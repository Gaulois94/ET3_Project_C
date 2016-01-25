#include "Contexts/InGame.h"

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
	self->map        = NULL;
	self->ennemies   = NULL;
	self->nbEnnemies = 0;
	SDL_Rect scoreRect;
	scoreRect.x = 10;
	scoreRect.y = 20;

	uint32_t nbLifes = DEFAULT_LIFE;

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

	self->player             = Player_create(0, 0);

	InGame_reinit((Context*)self);
	if(self->player == NULL)
	{
		perror("Error while loading the player \n");
		return;
	}

	((Context*)self)->run         = &InGame_run;
	((Context*)self)->updateEvent = &InGame_updateEvent;
	((Context*)self)->reinit      = &InGame_reinit;
}

void InGame_reinit(Context* context)
{
    InGame* self = (InGame*)context;
    Player_setSpeedY(self->player, 0);
	Player_setScancode(self->player, globalVar_jumpscancode, globalVar_leftscancode, globalVar_rightscancode);
	self->initTime = self->currentTime = SDL_GetTicks();
    if(self->map)
    {
        Map_destroy(self->map);
        self->map = NULL;
    }
	self->hasDied            = false;
	self->hasActivedGameOver = false;
	self->hasWon             = false;
	self->hasActivedWin      = false;
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
	if(self->map == NULL)
	{
		InGame_loadMap(self, "Resources/Tile.xml");
		if(self->map == NULL || globalVar_window == NULL)
			return NOTHING;
		SDL_Point start = Map_getStartCoords(self->map);
		const SDL_Rect* playerRect = Drawable_getRect((Drawable*)self->player);
		((Drawable*)self->player)->setPosition((Drawable*)self->player, start.x, start.y + self->map->caseSizeX - playerRect->h-1);
	}

	//We first update our datas
//	InGame_updateEnnemies(self);
	
	if(!self->hasDied && !self->hasWon)
	{
		InGame_updatePlayer(self);
		InGame_updateTime(self);
		InGame_updateCamera(self);
	}

	const SDL_Rect* rect = Drawable_getRect((Drawable*)self->player);
	if(Map_isOutside(self->map, rect->x, rect->y + rect->h) && Map_isOutside(self->map, rect->x + rect->w, rect->y + rect->h) || TIMEOUT-(self->currentTime - self->initTime)/1000 == 0)
    {
		self->hasDied = true;
		Player_stop(self->player);
    }

	//Then we display them;
	Map_draw(self->map, globalVar_window);
/* 	uint32_t i;
 	for(i=0; i < self->nbEnnemies; i++)
		self->ennemies[i]->draw(self->ennemies[i], globalVar_window->window);
*/
	Player_draw((Drawable*)(self->player), globalVar_window);
	InGame_drawUI(self);

	if(self->hasActivedGameOver)
	{
		self->nbLifes--;
		InGame_setLifeLabel(self);
		if(self->nbLifes == 0)
			return START;
		else
		{
			self->hasActivedGameOver = false;
			self->hasDied = false;
		}
	}

	if(self->hasActivedWin)
		return START;
	return NOTHING;
}

void InGame_updateEvent(Context* context, SDL_Event* event)
{
	InGame* self = (InGame*)context;

	if(self->hasDied && event->type == SDL_KEYDOWN)
	{
		self->hasActivedGameOver = true;
		if(self->nbLifes > 0)
		{
			if(self->map)
			{
				Map_destroy(self->map);
				self->map = NULL;
			}
		}
		return;
	}

	else if(self->hasWon && event->type == SDL_KEYDOWN)
	{
		self->hasActivedWin = true;
		return;
	}

	else
	{
		Active* player = (Active*)self->player;
		if(Active_updateEvents(player, event))
		{
			if(event->type == SDL_KEYDOWN && event->key.keysym.scancode == SDL_SCANCODE_UP)
				MusicManager_playSound(globalVar_musics, JUMP);
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

void InGame_updateEnnemies(InGame* self)
{

}

void InGame_updatePlayer(InGame* self)
{
	if(!self->map)
		return;

	const SDL_Rect* pRect = Drawable_getRect((Drawable*)self->player);

	Tile* topLeftTile=NULL;
	Tile* topRightTile=NULL;
	Tile* bottomLeftTile=NULL;
	Tile* bottomRightTile=NULL;

	//Update the player gravity
	Player_updateGravity(self->player);

	//Then check collisions
	pRect           = Drawable_getRect((Drawable*)self->player);
	bottomLeftTile  = Map_getTileInfo(self->map, pRect->x, pRect->y + pRect->h + 1); //+1 are here to check if we will be on collision if we move the player by gravity of 1 pixel.
	bottomRightTile = Map_getTileInfo(self->map, pRect->x + pRect->w, pRect->y + pRect->h + 1);
	topLeftTile     = Map_getTileInfo(self->map, pRect->x, pRect->y);
	topRightTile    = Map_getTileInfo(self->map, pRect->x + pRect->w, pRect->y);

	if(bottomLeftTile && (Tile_getInfo(bottomLeftTile) & SOLID) ||
	   bottomRightTile && (Tile_getInfo(bottomRightTile) & SOLID))
    {
		const SDL_Rect* tileRect;
		if(bottomRightTile)
		{
			bottomRightTile->updateCollision(bottomRightTile);
			tileRect = Drawable_getRect((Drawable*)bottomRightTile);
		}
		if(bottomLeftTile)
		{
			bottomLeftTile->updateCollision(bottomLeftTile);
			tileRect = Drawable_getRect((Drawable*)bottomLeftTile);
		}
		int32_t y = tileRect->y - 1;
		((Drawable*)self->player)->setPosition((Drawable*)self->player, pRect->x, y - pRect->h);
		Player_setSpeedY(self->player, 0);
    }

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

	else
		Player_setSpeedY(self->player, Player_getSpeedY(self->player) + GRAVITY);

	//Check if something solid is on our side
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
	if(bottomLeftTile && (Tile_getInfo(bottomLeftTile) & SCORE))
	{
		//Destroy it and add the score to the actual score.
		bottomLeftTile->updateCollision(bottomLeftTile);
		MusicManager_playSound(globalVar_musics, COIN_SOUND);
		InGame_addScore(self, 100);
	}
	   
	if(bottomRightTile && (Tile_getInfo(bottomRightTile) & SCORE) && bottomRightTile != bottomLeftTile)
	{
		bottomRightTile->updateCollision(bottomRightTile);
		MusicManager_playSound(globalVar_musics, COIN_SOUND);
		InGame_addScore(self, 100);
	}

	if(topLeftTile && (Tile_getInfo(topLeftTile) & SCORE) && topLeftTile != bottomLeftTile && topLeftTile != bottomRightTile)
	{
		topLeftTile->updateCollision(topLeftTile);
		MusicManager_playSound(globalVar_musics, COIN_SOUND);
		InGame_addScore(self, 100);
	}
	   
	if(topRightTile && (Tile_getInfo(topRightTile) & SCORE) && topRightTile != bottomLeftTile && topRightTile != bottomRightTile && topRightTile != topLeftTile)
	{
		topRightTile->updateCollision(topRightTile);
		MusicManager_playSound(globalVar_musics, COIN_SOUND);
		InGame_addScore(self, 100);
	}

	if(bottomLeftObject && (Object_getInfo(bottomLeftObject) & FINISH))
	{
		bottomLeftObject->updateCollision(bottomLeftObject);
		self->hasWon = true;
	}
	   
	if(bottomRightObject && (Object_getInfo(bottomRightObject) & FINISH) && bottomRightObject != bottomLeftObject)
	{
		bottomRightObject->updateCollision(bottomRightObject);
		self->hasWon = true;
	}

	if(topLeftObject && (Object_getInfo(topLeftObject) & FINISH) && topLeftObject != bottomLeftObject && topLeftObject != bottomRightObject)
	{
		topLeftObject->updateCollision(topLeftObject);
		self->hasWon = true;
	}
	   
	if(topRightObject && (Object_getInfo(topRightObject) & FINISH) && topRightObject != bottomLeftObject && topRightObject != bottomRightObject && topRightObject != topLeftObject)
	{
		topRightObject->updateCollision(topRightObject);
		self->hasWon = true;
	}
}

void InGame_updateCamera(InGame* self)
{
	const SDL_Rect* playerRect = Drawable_getRect((Drawable*)self->player);
	Window_setCameraCoords(globalVar_window, -SCREEN_WIDTH/2+playerRect->x+playerRect->w/2, -SCREEN_HEIGHT/2+playerRect->y+playerRect->h/2);

	if(self->map)
	{
		SDL_Rect mapRect = Map_getRect(self->map);
		if(globalVar_window->cameraX < mapRect.x)
			Window_setCameraCoords(globalVar_window, mapRect.x, globalVar_window->cameraY);
		else if(globalVar_window->cameraX + SCREEN_WIDTH > mapRect.x + mapRect.w)
			Window_setCameraCoords(globalVar_window, mapRect.x + mapRect.w - SCREEN_WIDTH, globalVar_window->cameraY);

		if(globalVar_window->cameraY + SCREEN_HEIGHT > mapRect.y + mapRect.h)
			Window_setCameraCoords(globalVar_window, globalVar_window->cameraX, mapRect.y + mapRect.h - SCREEN_HEIGHT);
	}
}

void InGame_addScore(InGame* self, uint32_t add)
{
	char score[9];
	sprintf(score, "%08d", add + self->score);
	self->score += add;
	Text_setText(self->scoreLabel, globalVar_window, score);
}

void InGame_loadMap(InGame* self, const char* path)
{
	if(self->map)
		Map_destroy(self->map);

	self->map = NULL;
	self->map = Map_create(path);
	if(self->map == NULL)
	{
		perror("Error while loading the map \n");
		return;
	}
	self->initTime = self->currentTime = SDL_GetTicks();
}

void InGame_updateTime(InGame* self)
{
	self->currentTime = SDL_GetTicks();
	char t[4];
	int32_t value = TIMEOUT-(self->currentTime - self->initTime)/1000;
	sprintf(t, "%03d", (value > 0) ? value : 0);
	Text_setText(self->timeLabel, globalVar_window, t);
}

bool InGame_updateLoose(InGame* self)
{
	return false;
}

void InGame_destroy(InGame* self)
{
	uint32_t i;
//	for(i=0; i < self->nbEnnemies; i++)
//		Ennemy_destroy(self->ennemies[i]);
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
	free(self);
}
