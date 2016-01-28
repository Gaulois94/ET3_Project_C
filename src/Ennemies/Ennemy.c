#include "Ennemies/Ennemy.h"

void Ennemy_init(Ennemy* self, SDL_Texture* texture, const SDL_Rect* subRect)
{
	Tile_init((Tile*)self, texture, subRect);
	((Tile*)self)->info |= ENNEMY;
	self->speedY = 0;
	self->moveX = 0;
	self->direction = DLEFT;
}
