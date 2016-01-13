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
	self->score       = Text_create(&scoreRect, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "00000000");
	((Drawable*)(self->score))->setStatic((Drawable*)(self->score), true);
	
	self->timeLabel       = Text_create(&scoreRect, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "000");
	const SDL_Rect* timeLabelRect = Drawable_getRect((Drawable*)(self->timeLabel));
	((Drawable*)(self->timeLabel))->setPosition((Drawable*)(self->timeLabel), SCREEN_WIDTH - 10 - timeLabelRect->w, SCREEN_HEIGHT - 20 - timeLabelRect->h);

	self->player     = Player_create(500, 400);
	if(self->player == NULL)
	{
		perror("Error while loading the player \n");
		return;
	}
	self->initTime = 0;

	((Context*)self)->run = &InGame_run;
}

EnumContext InGame_run(Context* context)
{
	InGame* self = (InGame*)context;
//	if(self->map == NULL || globalVar_window)
//		return 0;

	//We first update our datas
//	InGame_updateEnnemies(self);
//	InGame_updatePlayer(self);

	InGame_updateTime(self);

	//Then we display them
//	Map_draw(self->map, globalVar_window);
/* 	uint32_t i;
 	for(i=0; i < self->nbEnnemies; i++)
		self->ennemies[i]->draw(self->ennemies[i], globalVar_window->window);
*/
	Player_draw((Drawable*)(self->player), globalVar_window);
	
	InGame_drawUI(self);
}

void InGame_drawUI(InGame* self)
{
	((Drawable*)(self->timeLabel))->draw((Drawable*)(self->timeLabel), globalVar_window);
	((Drawable*)(self->score))->draw((Drawable*)(self->score), globalVar_window);
}

void InGame_updateEnnemies(InGame* self)
{

}

void InGame_updatePlayer(InGame* self)
{

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
	sprintf(t, "%3d", (value > 0) ? value : 0);
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
	if(self->score != NULL)
		Text_destroy((Drawable*)(self->score));
	if(self->timeLabel != NULL)
		Text_destroy((Drawable*)(self->timeLabel));
	free(self);
}
