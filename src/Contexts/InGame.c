#include "Contexts/InGame.h"
#include "globalVar.h"

InGame* InGame_create()
{
	InGame* self = (InGame*)malloc(sizeof(InGame));
	if(self == NULL)
	{
		perror("Error in malloc");
		free(self);
		return NULL;
	}
	InGame_init(self);
	return self;
}

void InGame_init(InGame* self)
{
	//Initialise all the variables
	self->map        = NULL;
	SDL_Rect scoreRect;
	scoreRect.x = 10;
	scoreRect.y = 20;

	//All the text
	self->scoreLabel       = Text_create(&scoreRect, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "00000000");
	((Drawable*)(self->scoreLabel))->setStatic((Drawable*)(self->scoreLabel), true);
	
	self->timeLabel       = Text_create(&scoreRect, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "000");
	((Drawable*)(self->timeLabel))->setStatic((Drawable*)(self->timeLabel), true);

	self->gameOver        = Text_create(&scoreRect, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "Game Over");
	self->winLabel        = Text_create(&scoreRect, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "Win");
	((Drawable*)(self->gameOver))->setStatic((Drawable*)(self->gameOver), true);
	((Drawable*)(self->winLabel))->setStatic((Drawable*)(self->winLabel), true);

	self->lifeText        = Text_create(&scoreRect, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "Life x3");
	((Drawable*)(self->lifeText))->setStatic((Drawable*)(self->lifeText), true);

	const SDL_Rect* timeLabelRect = Drawable_getRect((Drawable*)(self->timeLabel));
	((Drawable*)(self->timeLabel))->setPosition((Drawable*)(self->timeLabel), SCREEN_WIDTH - 10 - timeLabelRect->w, SCREEN_HEIGHT - 20 - timeLabelRect->h);
	((Drawable*)(self->gameOver))->setPosition((Drawable*)(self->gameOver), 360, 290);
	((Drawable*)(self->winLabel))->setPosition((Drawable*)(self->winLabel), 360, 290);
	((Drawable*)(self->lifeText))->setPosition((Drawable*)(self->lifeText), 380, 20);

	//The player
	self->player             = Player_create(0, 0);

	//Use reinit for not redo the work twice
	InGame_reinit((Context*)self);
	if(self->player == NULL)
	{
		perror("Error while loading the player \n");
		return;
	}

	//Set polymorphisme functions
	((Context*)self)->run         = &InGame_run;
	((Context*)self)->updateEvent = &InGame_updateEvent;
	((Context*)self)->reinit      = &InGame_reinit;
}

void InGame_reinit(Context* context)
{
	//Play the musique
	MusicManager_playBackground(globalVar_musics);

	//Init the player (gravity, button events)
    InGame* self = (InGame*)context;
    Player_setSpeedY(self->player, 0);
	Player_setScancode(self->player, globalVar_jumpscancode, globalVar_leftscancode, globalVar_rightscancode);

	//The time
	self->initTime = self->currentTime = SDL_GetTicks();

	//Destroy a map if we have one
    if(self->map)
    {
        Map_destroy(self->map);
        self->map = NULL;
    }

	//All events of the InGame context are reinit.
	self->hasDied            = false;
	self->hasActivedGameOver = false;
	self->hasWon             = false;
	self->hasActivedWin      = false;

	//The score
	self->score              = 0;
	InGame_addScore(self, 0);
	MusicManager_playBackground(globalVar_musics);

	self->nbLifes = DEFAULT_LIFE;
	InGame_setLifeLabel(self);
}

void InGame_setLifeLabel(InGame* self)
{
	char text[20];
	sprintf(text, "Life%s x%d", (self->nbLifes > 1) ? "s" : "", self->nbLifes);
	Text_setText(self->lifeText, globalVar_window, text);
}

EnumContext InGame_run(Context* context)
{
	SDL_SetRenderDrawColor(globalVar_window->renderer, 0x93, 0xbb, 0xec, 0xff);
	InGame* self = (InGame*)context;

	//If we haven't the map, we recreate it
	if(self->map == NULL)
	{
		InGame_loadMap(self, "Resources/Tile.xml");
		if(self->map == NULL || globalVar_window == NULL)
			return NOTHING;
		SDL_Point start = Map_getStartCoords(self->map);
		const SDL_Rect* playerRect = Drawable_getRect((Drawable*)self->player);
		((Drawable*)self->player)->setPosition((Drawable*)self->player, start.x, start.y + self->map->caseSizeX - playerRect->h-1);
	}

	//If the game continues
	if(!self->hasDied && !self->hasWon)
	{
		//Update it
		InGame_updatePlayer(self);
		InGame_updateTime(self);
		InGame_updateCamera(self);
	}

	//Look is we are outside the map
	const SDL_Rect* rect = Drawable_getRect((Drawable*)self->player);
	if(Map_isOutside(self->map, rect->x, rect->y + rect->h) && Map_isOutside(self->map, rect->x + rect->w, rect->y + rect->h) || TIMEOUT-(self->currentTime - self->initTime)/1000 == 0)
    {
		//Then we die
		self->hasDied = true;
		Player_stop(self->player);
    }

	//Then we display them;
	Map_draw(self->map, globalVar_window);
	Player_draw((Drawable*)(self->player), globalVar_window);
	InGame_drawUI(self);

	//We we have validate the game over
	if(self->hasActivedGameOver)
	{
		//We look about our current life
		self->nbLifes--;
		InGame_setLifeLabel(self);
		if(self->nbLifes == 0)
			return START; //And call the Start context if we loose
		//Or we redo the game
		else
		{
			self->hasActivedGameOver = false;
			self->hasDied = false;
			InGame_addScore(self, -self->score);
		}
	}

	if(self->hasActivedWin)
		return START;
	return NOTHING;
}

void InGame_updateEvent(Context* context, SDL_Event* event)
{
	InGame* self = (InGame*)context;

	//If we have die and the game over statement is activate
	if(self->hasDied && event->type == SDL_KEYDOWN)
	{
		self->hasActivedGameOver = true;
		if(self->nbLifes > 0)
		{
			if(self->map) //Destroy the map. It will be recreated in run function
			{
				Map_destroy(self->map);
				self->map = NULL;
			}
		}
		return;
	}

	//If we won and the win statement is activated
	else if(self->hasWon && event->type == SDL_KEYDOWN)
	{
		self->hasActivedWin = true;
		return;
	}

	else
	{
		//Update the player
		Active* player = (Active*)self->player;
		if(Active_updateEvents(player, event))
		{
			if(self->player->justHasJump)
				MusicManager_playSound(globalVar_musics, JUMP); //Play the sound "JUMP" if we have jump
			return;
		}
	}
}

void InGame_drawUI(InGame* self)
{
	((Drawable*)(self->timeLabel))->draw((Drawable*)(self->timeLabel), globalVar_window);
	((Drawable*)(self->scoreLabel))->draw((Drawable*)(self->scoreLabel), globalVar_window);
	((Drawable*)(self->lifeText))->draw((Drawable*)(self->lifeText), globalVar_window);
	if(self->hasDied)
		((Drawable*)(self->gameOver))->draw((Drawable*)(self->gameOver), globalVar_window);
	if(self->hasWon)
		((Drawable*)(self->winLabel))->draw((Drawable*)(self->winLabel), globalVar_window);
}

void InGame_updatePlayer(InGame* self)
{
	if(!self->map)
		return;

	//4 tiles / object / dynamic tiles are needed because the rect player has 4 points.
	Tile* topLeftTile         = NULL;
	Tile* topRightTile        = NULL;
	Tile* bottomLeftTile      = NULL;
	Tile* bottomRightTile     = NULL;

	Tile* topLeftDynamics     = NULL;
	Tile* topRightDynamics    = NULL;
	Tile* bottomLeftDynamics  = NULL;
	Tile* bottomRightDynamics = NULL;

	//Update the player gravity
	Player_updateGravity(self->player);

	//Then check collisions
	const SDL_Rect* pRect = Drawable_getRect((Drawable*)self->player);
	bottomLeftTile        = Map_getTileInfo(self->map, pRect->x, pRect->y + pRect->h + 1); //+1 are here to check if we will be on collision if we move the player by gravity of 1 pixel.
	bottomRightTile       = Map_getTileInfo(self->map, pRect->x + pRect->w, pRect->y + pRect->h + 1);
	topLeftTile           = Map_getTileInfo(self->map, pRect->x, pRect->y);
	topRightTile          = Map_getTileInfo(self->map, pRect->x + pRect->w, pRect->y);

	//If the tile on our foot is something SOLID, such as ground
	if(bottomLeftTile && (Tile_getInfo(bottomLeftTile) & SOLID) ||
	   bottomRightTile && (Tile_getInfo(bottomRightTile) & SOLID))
    {
		//Get the tile rect on where we entered in collision
		const SDL_Rect* tileRect;
		if(bottomRightTile)
		{
			bottomRightTile->updateCollision(bottomRightTile);
			tileRect = Drawable_getRect((Drawable*)bottomRightTile);
		}

		else if(bottomLeftTile)
		{
			bottomLeftTile->updateCollision(bottomLeftTile);
			tileRect = Drawable_getRect((Drawable*)bottomLeftTile);
		}
		int32_t y = tileRect->y - 1;
		((Drawable*)self->player)->setPosition((Drawable*)self->player, pRect->x, y - pRect->h); //The reposition the player correctly
		Player_setSpeedY(self->player, 0); //And set its gravity to 0
    }

	//The same for tile on our head
	else if(topLeftTile && (Tile_getInfo(topLeftTile) & SOLID) ||
	        topRightTile && (Tile_getInfo(topRightTile) & SOLID))
    {
		const SDL_Rect* tileRect;
		if(topRightTile)
		{
			topRightTile->updateCollision(topRightTile);
			tileRect = Drawable_getRect((Drawable*)topRightTile);
		}
		if(topLeftTile)
		{
			topLeftTile->updateCollision(topLeftTile);
			tileRect = Drawable_getRect((Drawable*)topLeftTile);
		}
		int32_t y = tileRect->y + tileRect->h + 1;
		((Drawable*)self->player)->setPosition((Drawable*)self->player, pRect->x, y);
		Player_setSpeedY(self->player, 0);
    }

	//We we aren't not on something, then we fall.
	else
		Player_setSpeedY(self->player, Player_getSpeedY(self->player) + GRAVITY);

    //Check on dynamic side
    bottomLeftDynamics  = Map_getDynamicTile(self->map, pRect->x, pRect->y + pRect->h);
    bottomRightDynamics = Map_getDynamicTile(self->map, pRect->x + pRect->w, pRect->y + pRect->h);

    uint32_t i;

	//Useful for not doing the work 4 times (we can use a loop)
	Tile* dynamicTile[4];
	dynamicTile[0] = bottomLeftDynamics;
	dynamicTile[1] = bottomRightDynamics;
	dynamicTile[2] = NULL;
	dynamicTile[3] = NULL;
	uint32_t dynamicTileID, sizeDynamicTile = 4;
	const SDL_Rect* r = Drawable_getRect((Drawable*)self->player);

	//Loop for checking collisions with all dynamic tiles
	for(dynamicTileID=0; dynamicTileID < sizeDynamicTile; dynamicTileID++)
	{
		//If we haven't a dynamic tile on this case
		if(!dynamicTile[dynamicTileID])
			continue;

		Tile* tile = dynamicTile[dynamicTileID];

		//Or if the dynamic tile is not an ennemy
		if(!(Tile_getInfo(tile) & ENNEMY))
			continue;

		//Or if the ennemy isn't destroyd yet (it lives)
		else if(tile && !tile->canDestroy)
		{
			//Look if indeed we are on collision. It is needed because dynamic tiles don't fit all the dynamic cases (definition of dynamic cases : all the tiles can be nowhere of any size.
			const SDL_Rect* tileRect = Drawable_getRect((Drawable*)tile);
			if(rectCollision(tileRect, pRect))
			{
				//If we fall, then the ennemy is killed
				if(self->player->speedY > 0)
				{
					InGame_addScore(self, 100);
					tile->canDestroy = true;
					Player_setSpeedY(self->player, JUMP_SPEED);
				}
			}
		}
	}

	//Check if something solid is on our side. We do the same thing that for falling.
	Player_updateMovement(self->player);
	pRect           = Drawable_getRect((Drawable*)self->player);
	bottomLeftTile  = Map_getTileInfo(self->map, pRect->x, pRect->y + pRect->h);
	bottomRightTile = Map_getTileInfo(self->map, pRect->x + pRect->w, pRect->y + pRect->h);
	topLeftTile     = Map_getTileInfo(self->map, pRect->x, pRect->y);
	topRightTile    = Map_getTileInfo(self->map, pRect->x + pRect->w, pRect->y);

	//on left
	if(bottomLeftTile && (Tile_getInfo(bottomLeftTile) & SOLID) ||
	   topLeftTile && (Tile_getInfo(topLeftTile) & SOLID))
    {
		const SDL_Rect* tileRect;
		if(topLeftTile)
		{
			topLeftTile->updateCollision(topLeftTile);
			tileRect = Drawable_getRect((Drawable*)topLeftTile);
		}
		if(bottomLeftTile)
		{
			bottomLeftTile->updateCollision(bottomLeftTile);
			tileRect = Drawable_getRect((Drawable*)bottomLeftTile);
		}

		uint32_t x = tileRect->x + tileRect->w + 1;
		((Drawable*)self->player)->setPosition((Drawable*)self->player, x, pRect->y);
    }

	//on right
	else if(topRightTile && (Tile_getInfo(topRightTile) & SOLID) ||
	        bottomRightTile && (Tile_getInfo(bottomRightTile) & SOLID))
    {
		const SDL_Rect* tileRect;
		if(topRightTile)
		{
			topRightTile->updateCollision(topRightTile);
			tileRect = Drawable_getRect((Drawable*)topRightTile);
		}
		if(bottomRightTile)
		{
			bottomRightTile->updateCollision(bottomRightTile);
			tileRect = Drawable_getRect((Drawable*)bottomRightTile);
		}

		int32_t x = tileRect->x - 1;
		((Drawable*)self->player)->setPosition((Drawable*)self->player, x - pRect->w, pRect->y);
    }

	//Reload tile information.
	pRect           = Drawable_getRect((Drawable*)self->player);
	bottomLeftTile  = Map_getTileInfo(self->map, pRect->x, pRect->y + pRect->h);
	bottomRightTile = Map_getTileInfo(self->map, pRect->x + pRect->w, pRect->y + pRect->h);
	topLeftTile     = Map_getTileInfo(self->map, pRect->x, pRect->y);
	topRightTile    = Map_getTileInfo(self->map, pRect->x + pRect->w, pRect->y);

	Object* bottomLeftObject  = Map_getObjectInfo(self->map, pRect->x, pRect->y + pRect->h);
	Object* bottomRightObject = Map_getObjectInfo(self->map, pRect->x + pRect->w, pRect->y + pRect->h);
	Object* topLeftObject     = Map_getObjectInfo(self->map, pRect->x, pRect->y);
	Object* topRightObject    = Map_getObjectInfo(self->map, pRect->x + pRect->w, pRect->y);

	//Then check if we are on a coin
	Tile* tiles[4];
	tiles[0] = bottomLeftTile;
	tiles[1] = bottomRightTile;
	tiles[2] = topRightTile;
	tiles[3] = topLeftTile;
	for(i=0; i < 4; i++)
	{
		if(tiles[i] && !tiles[i]->canDestroy && Tile_getInfo(tiles[i]) & SCORE)
		{
			tiles[i]->updateCollision(tiles[i]);
			MusicManager_playSound(globalVar_musics, COIN_SOUND);
			InGame_addScore(self, 100);
		}
	}

	Object* objects[4];
	objects[0] = bottomLeftObject;
	objects[1] = bottomRightObject;
	objects[2] = topLeftObject;
	objects[3] = topRightObject;

	for(i=0; i < 4; i++)
	{
		if(objects[i] && (Object_getInfo(objects[i]) & FINISH) && !self->hasWon)
		{
			objects[i]->updateCollision(objects[i]);
			self->hasWon = true;
		}
	}
	   
	//Then recheck on dynamic trace
    bottomLeftDynamics  = Map_getDynamicTile(self->map, pRect->x, pRect->y + pRect->h);
    bottomRightDynamics = Map_getDynamicTile(self->map, pRect->x + pRect->w, pRect->y + pRect->h);
    topLeftDynamics  = Map_getDynamicTile(self->map, pRect->x, pRect->y);
    topRightDynamics = Map_getDynamicTile(self->map, pRect->x + pRect->w, pRect->y);

	//Same thing that for falling
	dynamicTile[0] = bottomLeftDynamics;
	dynamicTile[1] = bottomRightDynamics;
	dynamicTile[2] = topRightDynamics;
	dynamicTile[3] = topLeftDynamics;
	for(dynamicTileID=0; dynamicTileID < sizeDynamicTile; dynamicTileID++)
	{
		if(!dynamicTile[dynamicTileID])
			continue;
		Tile* tile = dynamicTile[dynamicTileID];

		if(!(Tile_getInfo(tile) & ENNEMY))
			continue;

		else if(tile && !tile->canDestroy)
		{
			//Except that we die if we touch an ennemy
			const SDL_Rect* tileRect = Drawable_getRect((Drawable*)tile);
			if(rectCollision(tileRect, pRect))
			{
				self->hasDied = true;
				return;
			}
		}
	}
}

void InGame_updateCamera(InGame* self)
{
	//We first put the player on the center of the window
	const SDL_Rect* playerRect = Drawable_getRect((Drawable*)self->player);
	Window_setCameraCoords(globalVar_window, -SCREEN_WIDTH/2+playerRect->x+playerRect->w/2, -SCREEN_HEIGHT/2+playerRect->y+playerRect->h/2);

	//Then if we have a map we look if the camera isn't showing things outside of the map
	if(self->map)
	{
		SDL_Rect mapRect = Map_getRect(self->map);
		if(globalVar_window->cameraX < mapRect.x) //If we are far on the left
			Window_setCameraCoords(globalVar_window, mapRect.x, globalVar_window->cameraY);
		else if(globalVar_window->cameraX + SCREEN_WIDTH > mapRect.x + mapRect.w) //Or far on the right
			Window_setCameraCoords(globalVar_window, mapRect.x + mapRect.w - SCREEN_WIDTH, globalVar_window->cameraY);

		//If we are far on the bottom
		if(globalVar_window->cameraY + SCREEN_HEIGHT > mapRect.y + mapRect.h)
			Window_setCameraCoords(globalVar_window, globalVar_window->cameraX, mapRect.y + mapRect.h - SCREEN_HEIGHT);
		//Or far on the top
		else if(globalVar_window->cameraY < 0)
			Window_setCameraCoords(globalVar_window, globalVar_window->cameraX, 0);
	}
}

void InGame_addScore(InGame* self, uint32_t add)
{
	//Set the Text score
	char score[9];
	sprintf(score, "%08d", add + self->score);
	self->score += add;
	Text_setText(self->scoreLabel, globalVar_window, score);
}

void InGame_loadMap(InGame* self, const char* path)
{
	//Check if we have a map
	if(self->map)
		Map_destroy(self->map);
	//Then create it
	self->map = Map_create(path);
	if(self->map == NULL)
	{
		perror("Error while loading the map \n");
		return;
	}
	//Reinit the time
	self->initTime = self->currentTime = SDL_GetTicks();
}

void InGame_updateTime(InGame* self)
{
	//Update the text time and its value
	self->currentTime = SDL_GetTicks();
	char t[4];
	int32_t value = TIMEOUT-(self->currentTime - self->initTime)/1000;
	sprintf(t, "%03d", (value > 0) ? value : 0);
	Text_setText(self->timeLabel, globalVar_window, t);
}

void InGame_destroy(InGame* self)
{
	//Destroy everything
	if(self->map != NULL)
		Map_destroy(self->map);
	if(self->player != NULL)
		Player_destroy((Drawable*)(self->player));
	if(self->scoreLabel != NULL)
		Text_destroy((Drawable*)(self->scoreLabel));
	if(self->timeLabel != NULL)
		Text_destroy((Drawable*)(self->timeLabel));
	if(self->gameOver != NULL)
		Text_destroy((Drawable*)(self->gameOver));
	if(self->winLabel != NULL)
		Text_destroy((Drawable*)(self->winLabel));
	if(self->lifeText)
		Text_destroy((Drawable*)(self->lifeText));
	free(self);
}
