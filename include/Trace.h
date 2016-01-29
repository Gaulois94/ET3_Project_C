#ifndef  TRACE_INC
#define  TRACE_INC

#include "Tiles/Tile.h"
#include "List.h"
#include "Datas.h"
#include "File.h"

/** \struct StaticTrace
 * \brief Static trace is a Trace about static tiles. The map is squared such as static traces. Each tile has the same size and a position on the squared trace*/
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

/** \struct DynamicTrace
 * \brief Dynamic Trace is for dynamic traces. Each tile has an absolute position and isn't bind to a squared position. But for collisions, we keep squared the dynamic trace.*/
typedef struct
{
	List*** tiles;
	uint32_t sizeX;
	uint32_t sizeY;
	uint32_t nbCasesX;
	uint32_t nbCasesY;
}DynamicTrace;

DynamicTrace* DynamicTrace_create(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY);
void DynamicTrace_addTile(DynamicTrace* self, Tile* tile);
void DynamicTrace_draw(DynamicTrace* self, Window* window);
void DynamicTrace_destroy(DynamicTrace* self);
List* DynamicTrace_getList(DynamicTrace* self, uint32_t x, uint32_t y);
Tile* DynamicTrace_getTile(DynamicTrace* self, uint32_t x, uint32_t y);

StaticTrace* StaticTrace_create(uint32_t sizeX, uint32_t sizeY, uint32_t nbCasesX, uint32_t nbCasesY,
								  uint32_t padX, uint32_t padY);
void    StaticTrace_addTile(StaticTrace* self, Tile* tile, uint32_t x, uint32_t y);
void    StaticTrace_addObject(StaticTrace* self, Object* object, uint32_t x, uint32_t y);
Tile*   StaticTrace_getTile(StaticTrace* self, int32_t x, int32_t y);
Object* StaticTrace_getObject(StaticTrace* self, int32_t x, int32_t y);
void    StaticTrace_draw(StaticTrace* self, Window* window);
void    StaticTrace_destroy(StaticTrace* self, bool deleteTiles);

#endif
