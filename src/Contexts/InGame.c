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

	self->scoreLabel       = Text_create(&scoreRect, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "00000000");
	self->score = 0;
	((Drawable*)(self->scoreLabel))->setStatic((Drawable*)(self->scoreLabel), true);
	
	self->timeLabel       = Text_create(&scoreRect, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "000");
	((Drawable*)(self->timeLabel))->setStatic((Drawable*)(self->timeLabel), true);

	const SDL_Rect* timeLabelRect = Drawable_getRect((Drawable*)(self->timeLabel));
	((Drawable*)(self->timeLabel))->setPosition((Drawable*)(self->timeLabel), SCREEN_WIDTH - 10 - timeLabelRect->w, SCREEN_HEIGHT - 20 - timeLabelRect->h);

	self->player     = Player_create(0, 0);
	if(self->player == NULL)
	{
		perror("Error while loading the player \n");
		return;
	}
	self->initTime = 0;

	((Context*)self)->run = &InGame_run;
	((Context*)self)->updateEvent = &InGame_updateEvent;
}

EnumContext InGame_run(Context* context)
{
	InGame* self = (InGame*)context;
	if(self->map == NULL)
		InGame_loadMap(self, "Resources/Tile.xml");
	if(self->map == NULL || globalVar_window == NULL)
		return NOTHING;

	//We first update our datas
//	InGame_updateEnnemies(self);
	InGame_updatePlayer(self);
	InGame_updateTime(self);
	InGame_updateCamera(self);

	//Then we display them
	Map_draw(self->map, globalVar_window);
/* 	uint32_t i;
 	for(i=0; i < self->nbEnnemies; i++)
		self->ennemies[i]->draw(self->ennemies[i], globalVar_window->window);
*/
	Player_draw((Drawable*)(self->player), globalVar_window);
	
	InGame_drawUI(self);
}

void InGame_updateEvent(Context* context, SDL_Event* event)
{
	InGame* self = (InGame*)context;
	Active* player = (Active*)self->player;
	if(Active_updateEvents(player, event))
		return;
}

void InGame_drawUI(InGame* self)
{
	((Drawable*)(self->timeLabel))->draw((Drawable*)(self->timeLabel), globalVar_window);
	((Drawable*)(self->scoreLabel))->draw((Drawable*)(self->scoreLabel), globalVar_window);
}

void InGame_updateEnnemies(InGame* self)
{

}

void InGame_updatePlayer(InGame* self)
{
	if(!self->map)
		return;

	((Active*)(self->player))->update((Active*)(self->player));
	const SDL_Rect* pRect = Drawable_getRect((Drawable*)self->player);

	Tile* topLeftTile=NULL;
	Tile* topRightTile=NULL;
	Tile* bottomLeftTile=NULL;
	Tile* bottomRightTile=NULL;

	//Get the tile information
	bottomLeftTile  = Map_getTileInfo(self->map, pRect->x, pRect->y + pRect->h);
	bottomRightTile = Map_getTileInfo(self->map, pRect->x + pRect->w, pRect->y + pRect->h);
	topLeftTile     = Map_getTileInfo(self->map, pRect->x, pRect->y);
	topRightTile    = Map_getTileInfo(self->map, pRect->x + pRect->w, pRect->y);

	//Check if we are on a coin
	if(bottomLeftTile && (Tile_getInfo(bottomLeftTile) & SCORE))
	{
		//The destroy it and add the score to the actual score.
		bottomLeftTile->updateCollision(bottomLeftTile);
		InGame_addScore(self, 100);
	}
	   
	if(bottomRightTile && (Tile_getInfo(bottomRightTile) & SCORE))
	{
		bottomRightTile->updateCollision(bottomRightTile);
		InGame_addScore(self, 100);
	}

	if(topLeftTile && (Tile_getInfo(topLeftTile) & SCORE))
	{
		//The destroy it and add the score to the actual score.
		topLeftTile->updateCollision(topLeftTile);
		InGame_addScore(self, 100);
	}
	   
	if(topRightTile && (Tile_getInfo(topRightTile) & SCORE))
	{
		topRightTile->updateCollision(topRightTile);
		InGame_addScore(self, 100);
	}

	//Then replace correctly the player
	if(bottomLeftTile && (Tile_getInfo(bottomLeftTile) & SOLID) ||
	   bottomRightTile && (Tile_getInfo(bottomRightTile) & SOLID))
    {
        uint32_t y = pRect->y + pRect->h;
        if(bottomLeftTile)
        {
			bottomLeftTile->updateCollision(bottomLeftTile);
            const SDL_Rect* tileRect = Drawable_getRect((Drawable*)bottomLeftTile);
            y = tileRect->y + tileRect->h;
        }
        if(bottomRightTile)
        {
			bottomRightTile->updateCollision(bottomRightTile);
            const SDL_Rect* tileRect = Drawable_getRect((Drawable*)bottomRightTile);
            y = fmin(y, tileRect->y + tileRect->h);
        }
		((Drawable*)self->player)->setPosition((Drawable*)self->player, pRect->x, y - pRect->h);
		Player_setSpeedY(self->player, 0);
    }
	else
		Player_setSpeedY(self->player, Player_getSpeedY(self->player) + GRAVITY);
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
	int32_t value = 400-(self->currentTime - self->initTime)/1000;
	sprintf(t, "%03d", (value > 0) ? value : 0);
	Text_setText(self->timeLabel, globalVar_window, t);
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
	free(self);
}
