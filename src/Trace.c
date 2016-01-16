#include "Trace.h"

StaticTrace* StaticTrace_create(uint32_t sizeX, uint32_t sizeY, uint32_t nbCasesX, uint32_t nbCasesY,
								  uint32_t padX, uint32_t padY)
{
	StaticTrace* self = (StaticTrace*)malloc(sizeof(StaticTrace));
	if(self == NULL)
		return NULL;
	self->sizeX = sizeX;
	self->sizeY = sizeY;
	self->padX  = padX;
	self->padY  = padY;
	self->nbCasesX = nbCasesX;
	self->nbCasesY = nbCasesY;

	self->tiles = (Tile***)malloc(nbCasesX * sizeof(Tile**));
	self->objects = (Object***)malloc(nbCasesX * sizeof(Object**));
	uint32_t i,j;
	for(i=0; i < nbCasesX; i++)
	{
		self->tiles[i] = (Tile**)malloc(nbCasesY * sizeof(Tile*));
		self->objects[i] = (Object**)malloc(nbCasesY * sizeof(Object*));
		for(j=0; j < nbCasesY; j++)
		{
			self->tiles[i][j] = NULL;
			self->objects[i][j] = NULL;
		}
	}

	return self;
}

void StaticTrace_draw(StaticTrace* self, Window* window)
{
	uint32_t i, j;
	for(i=0; i < self->nbCasesX; i++)
	{
		for(j=0; j < self->nbCasesY; j++)
		{
			if(self->tiles[i][j])
				((Drawable*)self->tiles[i][j])->draw((Drawable*)self->tiles[i][j], window);
			else if(self->objects[i][j])
				((Drawable*)self->objects[i][j])->draw((Drawable*)self->objects[i][j], window);
		}
	}
}

void StaticTrace_addTile(StaticTrace* self, Tile* tile, uint32_t x, uint32_t y)
{
	if(x < self->nbCasesX && y < self->nbCasesY && tile)
	{
		self->tiles[x][y] = tile;
		Drawable* tileDrawable = (Drawable*)tile;
		tileDrawable->setPosition(tileDrawable, self->padX + x*self->sizeX, self->padY + y*self->sizeY);
	}
}

void StaticTrace_addObject(StaticTrace* self, Object* object, uint32_t x, uint32_t y)
{
	if(x < self->nbCasesX && y < self->nbCasesY && object)
	{
		self->objects[x][y] = object;
		Drawable* objectDrawable = (Drawable*)object;
		objectDrawable->setPosition(objectDrawable, self->padX + x*self->sizeX, self->padY + y*self->sizeY);
	}
}

void StaticTrace_destroy(StaticTrace* self, bool deleteTiles)
{
	uint32_t i, j;
	for(i=0; i < self->nbCasesX; i++)
	{
		if(deleteTiles)
		{
			for(j=0; j < self->nbCasesY; j++)
			{
				Drawable* tile = (Drawable*)(self->tiles[i][j]);
				Drawable* object = (Drawable*)(self->objects[i][j]);
				if(tile != NULL)
					tile->destroy(tile);
				if(object != NULL)
					object->destroy(object);
			}
		}
		free(self->tiles[i]);
		free(self->objects[i]);
	}
	free(self->tiles);
	free(self->objects);
	free(self);
}
