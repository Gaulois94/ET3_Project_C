#ifndef  TRACE_INC
#define  TRACE_INC

#include "Tiles/Tile.h"
#include "List.h"
#include "Datas.h"
#include "File.h"

typedef struct
{
	Tile*** tiles; //2D array which place tiles on the map
	Object*** objects; //2D array which place objects on the map
	uint32_t nbCasesX;
	uint32_t nbCasesY;
	uint32_t sizeX;
	uint32_t sizeY;
	uint32_t padX;
	uint32_t padY;
}StaticTrace;

typedef struct
{
	Tile** tiles;
}DynamicTrace;

DynamicTrace* DynamicTrace_create();
void DynamicTrace_addTile(DynamicTrace* self, Tile* tile);
void DynamicTrace_draw(DynamicTrace* self, Window* window);
void DynamicTrace_destroy(DynamicTrace* self, bool deleteTiles);

StaticTrace* StaticTrace_create(uint32_t sizeX, uint32_t sizeY, uint32_t nbCasesX, uint32_t nbCasesY,
								  uint32_t padX, uint32_t padY);
void  StaticTrace_addTile(StaticTrace* self, Tile* tile, uint32_t x, uint32_t y);
void  StaticTrace_addObject(StaticTrace* self, Object* object, uint32_t x, uint32_t y);
Tile* StaticTrace_getTile(StaticTrace* self, int32_t x, int32_t y);
void  StaticTrace_draw(StaticTrace* self, Window* window);
void  StaticTrace_destroy(StaticTrace* self, bool deleteTiles);

#endif
