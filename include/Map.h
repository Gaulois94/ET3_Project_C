#ifndef  MAP_INC
#define  MAP_INC

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "expat.h"
#include "ResourcesManager.h"
#include "Tiles/Tile.h"
#include "Tiles/Ground.h"
#include "Tiles/Coin.h"
#include "Tiles/DefaultTile.h"
#include "Tiles/TileStart.h"
#include "Ennemies/Goomba.h"
#include "IAs/basic.h"
#include "Objects/Object.h"
#include "Objects/Finish.h"
#include "Trace.h"
#include "csv.h"
#include "List.h"
#include "File.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "Datas.h"

/** \struct StaticFile
 * \brief Store all the datas about static files*/
typedef struct
{
	File* file;

	List* tileDatas; /** <! List of tile datas*/
	uint32_t spacingX;
	uint32_t spacingY;
	uint32_t tileSizeX;
	uint32_t tileSizeY;
}StaticFile;

/** \struct DynamicFile
 * \brief store dynamic files and its entities*/
typedef struct
{
	File* file;
	ResourcesManager* dynamicEntities;
}DynamicFile;


/**\struct Map
 * \brief Store all the content of a map
 * The xml format file is like this :
 * <map>
 *	<Window numberCase="axb" tileSize="axb" title="title"/>
 *
 *	<Files>
 *	 <Static file="path" spacing="axb" tileSize="axb">
 *	  <StaticTile name="name" type="type"/>
 *	 </Static>
 *	 <Dynamic file="path"> //Used for animation
 *	  <DynamicEntity name="name">
 *	   <DynamicTile name="name" pos="axb" size="axb" type="type"/>
 *	  </DynamicEntity>
 *	 </Dynamic>
 *	</Files>
 *
 *  <Objects name="name" numberCases = "axb" tileSize="axb" type="type">
 *   <ObjectsColumn fileID="fileID" tileID="tileID"/>
 *  </Objects>
 *
 *  <Traces>
 *   <StaticTrace name="name" shift="axb" size="axb">
 *    <Column fileID="fileID" tileID="tileID" objectID="objectID"/>
 *   </StaticTraces>
 *   <DynamicTrace name="name">
 *    <DynamicTile animName="name" animeTime="time" fileID="fileID" origin="axb" position="axb" tileID="tileID"/>
 *    <StaticTile fileID="fileID" tileID="tileID" position="axb"/>
 *   </DynamicTrace>
 *  </Traces>
 * </map> 
 *
 * each fileID et tileID are represented in csv format for StaticTrace. It earns us some time process and file spaces
 * axb = coordX . coordY
 * */
typedef struct
{
	XML_Parser parser;

	uint32_t nbCasesX;
	uint32_t nbCasesY;

	uint32_t caseSizeX;
	uint32_t caseSizeY;

	//The point is on the top left of the tile
	int32_t startX;
	int32_t startY;

	List* files;
	List* staticFiles;
	List* staticTraces;
	List* dynamicTraces;
	List* dynamicFiles;
	List* objects;
}Map;


Map* Map_create(const char* filePath);

/** \brief Default fonction called on a new element of the XML
 * \param name the name of the section
 * \param attrs the attributes of the section
 *  */
void startElement(void *map, const char* name, const char** attrs);

/** \brief Parse the section Trace of the XML
 * \param name the name of the section
 * \param attrs the attributes of the section
 *  */
void startElementFiles(void *map, const char* name, const char** attrs);

/** \brief Parse the section Trace of the XML
 * \param name the name of the section
 * \param attrs the attributes of the section
 *  */
void startElementObjects(void *map, const char* name, const char** attrs);

/** \brief Parse the section Trace of the XML
 * \param name the name of the section
 * \param attrs the attributes of the section
 *  */
void startElementTraces(void *map, const char* name, const char** attrs);

/** \brief Function called after that the section is readed
 * \param name the name of the section
 * \param attrs the attributes of the section
 *  */
void endElement(void *map, const char* name);

/** \brief extract x and y from a str like xxy where the second x is a cross
 * \param str the str
 * \param x pointer to store the x coordinate
 * \param y pointer to store the y coordinate
 *  */
void getXYFromStr(const char* str, uint32_t* x, uint32_t* y);

/** \brief draw the map
 * \param self the map
 * \param the window to draw*/
void Map_draw(Map* self, Window* window);

/** \brief Get the first dynamic tile on the x, y coordinate
 * \param self the map
 * \param x the x coordinate
 * \param y the y coordinate
 * \return Tile the tile. Returns Null if not found*/
Tile*     Map_getDynamicTile(Map* self, uint32_t x, uint32_t y);

/** \brief Get the List of dynamic tiles on the x, y coordinate
 * \param self the map
 * \param x the x coordinate
 * \param y the y coordinate
 * \return List found. Returns Null if not found*/
List*     Map_getDynamicList(Map* self, uint32_t x, uint32_t y);
SDL_Rect  Map_getRect(Map* self);
Tile*     Map_getTileInfo(Map* self, int32_t x, int32_t y);
Object*   Map_getObjectInfo(Map* self, int32_t x, int32_t y);
SDL_Point Map_getStartCoords(Map* self);
bool      Map_isOutside(Map* self, int32_t x, int32_t y);
void      Map_destroy(Map* map);

StaticFile*  StaticFile_create(File* file, uint32_t tileSizeX, uint32_t tileSizeY, uint32_t spacingX, uint32_t spacingY);
List*        StaticFile_getTiles(StaticFile* self);
Tile*        StaticFile_createTile(StaticFile* self, int32_t tileID, bool def);
void         StaticFile_destroy(StaticFile* self);

DynamicFile* DynamicFile_create(File* file);
void DynamicFile_destroy(DynamicFile* self);

extern uint32_t XML_depth;
extern uint32_t XML_NthColumn;

#endif
