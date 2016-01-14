#ifndef  TRACE_INC
#define  TRACE_INC

typedef struct
{
	Tile*** tiles; //2D array which place tiles on the map
	EnumTile** tileTypes; //2D array which tell the type per tiles
}StaticTrace;

typedef struct
{
	Tile** tiles;
	EnumTile** tileType;
}DynamicTrace;

typedef struct
{
	Tile*(*createStaticTile)(const SDL_Rect*, const SDL_Rect*);
	char* type;
}StaticTileDatas;

typedef struct
{
	File* file;

	List* tileRects;
	Tile(*createDynamicTile)(const SDL_Rect*, const List*, int, int);
}DynamicEntity;

DynamicTrace* DynamicTrace_create(uint32_t sizeX, uint32_t sizeY, uint32_t nbCaseX, uint32_t nbCaseY,
								  uint32_t padX, uint32_t padY);
void DynamicTrace_addTile(DynamicTrace* self, Tile* tile);
void DynamicTrace_draw(DynamicTrace* self, Window* window);
void DynamicTrace_destroy(DynamicTrace* self, bool deleteTiles);

StaticTrace* StaticTrace_create();
void StaticTrace_addTile(StaticTrace* self, Tile* tile, uint32_t x, uint32_t y);
void StaticTrace_draw(StaticTrace* self, Window* window);
void StaticTrace_destroy(StaticTrace* self, bool deleteTiles);

#endif
