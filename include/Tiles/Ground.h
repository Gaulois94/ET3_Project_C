#ifndef  GROUND_INC
#define  GROUND_INC

#include "Tiles/Tile.h"

typedef struct Ground
{
	Tile base;
}Ground;

Ground* Ground_create(const SDL_Rect* destRect);
void    Ground_init(Ground* self, const SDL_Rect* destRect);
uint32_t Ground_updateCollision(Ground* self);

#endif
