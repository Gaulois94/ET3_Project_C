#include "Ennemies/Goomba.h"

Tile* Goomba_create(const SDL_Rect* dest, SDL_Texture* texture, const SDL_Rect** rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame)
{
	Goomba* self = (Goomba*)malloc(sizeof(Goomba));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	Goomba_init(self, dest, texture, rectAnimation, maxN, currentN, nbFrame);
	return (Tile*)self;
}

void  Goomba_init(Goomba* self, const SDL_Rect* dest, SDL_Texture* texture, const SDL_Rect** rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame)
{
	Ennemy_init((Ennemy*)self, texture, dest);
	Tile* tile = (Tile*)self;
	tile->info = ENNEMY | SOLID;
	tile->sprite = (Sprite*)DynamicAnimation_create(dest, texture, rectAnimation, maxN, currentN, nbFrame);
}
