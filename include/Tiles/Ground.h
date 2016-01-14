#ifndef  GROUND_INC
#define  GROUND_INC

#include "Tiles/Tile.h"

typedef struct Ground
{
	Tile base;
}Ground;

Tile* Ground_create();
void    Ground_init(Ground* self);
uint32_t Ground_updateCollision(Tile* self);

#endif
