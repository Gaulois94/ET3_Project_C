#include "Object.h"

Object* Object_create(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY, int32_t posX, int32_t posY)
{
	Object* self = (Object*)malloc(sizeof(Object));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	Object_init(self, nbCasesX, nbCasesY, sizeX, sizeY, posX, posY);
	return self;
}

void Object_init(Object* self, uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY, int32_t posX, int32_t posY)
{
	Drawable* drawable = (Drawable*)self;
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = sizeX * nbCasesX;
	rect.h = sizeY * nbCasesY;
	Drawable_init(drawable, &rect);
	self->sizeX = sizeX;
	self->sizeY = sizeY;
	self->nbCaseX = nbCasesX;
	self->nbCaseY = nbCasesY;
	self->tiles = (Tile***)malloc(nbCasesX * sizeof(Tile**));
	uint32_t i=0;
	for(i=0; i < nbCasesX; i++)
		self->tiles[i] = (Tile**)malloc(nbCasesY * sizeof(Tile*));

	drawable->setPosition = &Object_setPosition;
	drawable->setSize     = &Object_setSize;
	drawable->setStatic   = &Object_setStatic;
	drawable->draw        = &Object_draw;
	drawable->destroy     = &Object_destroy;

	drawable->setPosition(drawable, posX, posY);
}

void Object_addTile(Object* self, uint32_t x, uint32_t y, Tile* tile)
{
	if(x >= self->nbCasesX && y >= self->nbCasesY)
		return;
	self->tiles[x][y] = tile;
}

void Object_setPosition(Drawable* drawable, int32_t x, int32_t y)
{
	Object* self = (Object*)drawable;
	uint32_t i, j;
	const SDL_Rect* rect = drawable->getRect(drawable);
	float factorX = rect->w / (float)(self->nbCasesX * self->sizeX);
	float factorY = rect->h / (float)(self->nbCasesY * self->sizeY);
	for(i=0; i < self->nbCasesX; i++)
	{
		for(j=0; j < self->nbCasesY; j++)
		{
			if(self->tiles[i][j])
			{
				Drawable* tile = (Drawable*)(self->tiles[i][j]);
				tile->setPosition(tile, x + factorX * self->sizeX * i, y + factorY * self->sizeY * j);
			}
		}
	}

	Drawable_setPosition(drawable, x, y);
}

void Object_setSize(Drawable* drawable, uint32_t width, uint32_t height)
{
	Object* self = (Object*)drawable;
	Drawable_setSize(drawable, width, height);
	self->setPosition(width, height);

	float factorX = width / (float)(self->nbCasesX * self->sizeX);
	float factorY = height / (float)(self->nbCasesY * self->sizeY);
	for(i=0; i < self->nbCasesX; i++)
	{
		for(j=0; j < self->nbCasesY; j++)
		{
			if(self->tiles[i][j])
			{
				Drawable* tile = (Drawable*)(self->tiles[i][j]);
				tile->setSize(tile, factorX * self->sizeX, factorY * self->sizeY);
			}
		}
	}
}
