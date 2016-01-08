#ifndef  TILE_INC
#define  TILE_INC

#include "Element.h"

typedef struct
{
	uint32_t x; //Coords in the tile map (not in pixels)
	uint32_t y;

	uint8_t solid;
	uint8_t doDamages;
}Tile;

#endif
