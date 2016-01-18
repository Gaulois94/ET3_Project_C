#ifndef  OBJECT_INC
#define  OBJECT_INC

#include "SDL2/SDL.h"
#include "Tiles/Tile.h"
#include "Drawable/Drawable.h"

typedef struct
{
	Drawable base;
	uint32_t info;
	Tile*** tiles;
	uint32_t nbCasesX;
	uint32_t nbCasesY;
	uint32_t sizeX;
	uint32_t sizeY;
}Object;

Object* Object_create(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY);
void    Object_init(Object* self, uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY);
void    Object_addTile(Object* self, uint32_t x, uint32_t y, Tile* tile);
void    Object_setPosition(Drawable* drawable, int32_t x, int32_t y);
void    Object_setSize(Drawable* drawable, uint32_t width, uint32_t height);
void    Object_setStatic(Drawable* drawable, bool isStatic);
void    Object_draw(Drawable* drawable, Window* window);
int32_t Object_getInfo(Object* object);
void    Object_destroy(Drawable* drawable);

#endif
