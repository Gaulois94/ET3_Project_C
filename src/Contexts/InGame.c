#include "Contexts/InGame.h"

InGame* InGame_create()
{
	InGame* self = (InGame*)malloc(sizeof(InGame));
	if(self == NULL)
	{
		perror("Error in malloc");
		return NULL;
	}
	return self;
}

void InGame_init(InGame* self)
{
	self->map        = NULL;
	self->ennemies   = NULL;
	self->nbEnnemies = 0;

	self->player     = Player_create();

	((Context*)self)->run = &InGame_run;
}

EnumContext InGame_run(Context* context)
{
	InGame* self = (InGame*)context;
	if(self->map == NULL || globalVar_window)
		return 0;

	//We first update our datas
	InGame_updateEnnemies(self);
	InGame_updatePlayer(self);

	//Then we display them
	Map_draw(self->map, globalVar_window->renderer);
	uint32_t i;
/* 	for(i=0; i < self->nbEnnemies; i++)
		self->ennemies[i]->draw(self->ennemies[i], globalVar_window->renderer);

	self->player->draw(self->player, globalVar_window->renderer);
	*/
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
}

void InGame_destroy(InGame* self)
{
	uint32_t i;
//	for(i=0; i < self->nbEnnemies; i++)
//		Ennemy_destroy(self->ennemies[i]);
	if(self->map)
		Map_destroy(self->map);
	if(self->player)
		Player_destroy(self->player);
}
