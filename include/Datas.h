#ifndef  DATAS_INC
#define  DATAS_INC

#include "Tiles/Tile.h"
#include "File.h"
#include "List.h"
#include "Objects/Object.h"

typedef struct
{
	Tile*(*createStaticTile)(SDL_Texture*, const SDL_Rect*);
//	char* type;
}StaticTileDatas;

typedef struct
{
	Object*(*createObject)(uint32_t, uint32_t, uint32_t, uint32_t);
	List* CSVTileID;
	List* CSVFileID;
	uint32_t nbCasesX;
	uint32_t nbCasesY;
	uint32_t tileSizeX;
	uint32_t tileSizeY;
}ObjectDatas;

typedef struct
{
	File* file;

	List* tileRects;
	Tile(*createDynamicTile)(const SDL_Rect*, const List*, int, int);
}DynamicEntity;

ObjectDatas* ObjectDatas_create();
void ObjectDatas_destroy(ObjectDatas* objDatas);

#endif   /* ----- #ifndef DATAS_INC  ----- */
