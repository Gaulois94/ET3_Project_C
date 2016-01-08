#ifndef  MAP_INC
#define  MAP_INC

#include "Tiles/Tile.h"

#define NB_TYPE_TILES 255

typedef struct
{
	Tile*** tiles; //2D array which place tiles on the map
	EnumTile** tileTypes; //2D array which tell the type per tiles

	uint32_t nbCaseX;
	uint32_t nbCaseY;

	uint32_t caseSizeX;
	uint32_t caseSizeY;
}Map;

#endif
