#ifndef  DATAS_INC
#define  DATAS_INC

#include "Tiles/Tile.h"
#include "File.h"
#include "List.h"
#include "Objects/Object.h"
#include "stdint.h"
#include "csv.h"

/** \struct StaticTileDatas
 * \brief keep datas about static File. In fact it keeps a pointer to the create function about a Tile.
 * */
typedef struct
{
	Tile*(*createStaticTile)(SDL_Texture*, const SDL_Rect*);
}StaticTileDatas;

/** \struct ObjectDatas
 * \brief jeeo datas about objects. In fact, it keeps CSV string about tiles and files (where to look for creating tiles which will create the Object), and the Object characteristics, such as tileSize and nbCases*/
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

/** \struct DynamicEntity
 * \brief Keep dynamic entitiy information.*/
typedef struct
{
	List* tileRects;
	Tile*(*createDynamicTile)(const SDL_Rect*, SDL_Texture*, const SDL_Rect**, uint32_t, uint32_t, uint32_t);
	void(*update)(Tile*, void*);
	void* data;
}DynamicEntity;

/** \brief create and initialise an Object*/
ObjectDatas* ObjectDatas_create();
void ObjectDatas_destroy(ObjectDatas* objDatas);

#endif   /* ----- #ifndef DATAS_INC  ----- */
