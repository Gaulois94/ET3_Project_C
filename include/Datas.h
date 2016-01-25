#ifndef  DATAS_INC
#define  DATAS_INC

#include "Tiles/Tile.h"
#include "File.h"
#include "List.h"
#include "Objects/Object.h"
#include "stdint.h"

typedef struct
{
	Tile*(*createStaticTile)(SDL_Texture*, const SDL_Rect*);
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
	List* tileRects;
	Tile*(*createDynamicTile)(const SDL_Rect*, SDL_Texture*, SDL_Rect*, uint32_t, uint32_t, uint32_t);
}DynamicEntity;

ObjectDatas* ObjectDatas_create();
void ObjectDatas_destroy(ObjectDatas* objDatas);

#endif   /* ----- #ifndef DATAS_INC  ----- */
