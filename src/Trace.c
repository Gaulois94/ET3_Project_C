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
			{
				if(self->tiles[i][j]->canDestroy)
				{
					((Drawable*)self->tiles[i][j])->destroy((Drawable*)(self->tiles[i][j]));
					self->tiles[i][j] = NULL;
				}
				else
					((Drawable*)self->tiles[i][j])->draw((Drawable*)self->tiles[i][j], window);
			}
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

Tile* StaticTrace_getTile(StaticTrace* self, int32_t x, int32_t y)
{
	if(x < 0 || y < 0 ||
	   x >= self->nbCasesX * self->sizeX - self->padX || y >= self->nbCasesY * self->sizeY - self->padY)
		return NULL;
	return self->tiles[(x - self->padX)/self->sizeX][(y - self->padY)/self->sizeY];
}

Object* StaticTrace_getObject(StaticTrace* self, int32_t x, int32_t y)
{
	if(x < 0 || y < 0 ||
	   x >= self->nbCasesX * self->sizeX - self->padX || y >= self->nbCasesY * self->sizeY - self->padY)
		return NULL;

	uint32_t indiceX = (x - self->padX)/self->sizeX;
	uint32_t indiceY = (y - self->padY)/self->sizeY;
	uint32_t i, j;
	for(i=0; i <= indiceX; i++)
	{
		for(j=0; j <= indiceY; j++)
		{
			if(self->objects[i][j])
			{
				if(self->objects[i][j]->nbCasesX + i > indiceX && 
						self->objects[i][j]->nbCasesY + j > indiceY)
					return self->objects[i][j];
			}
		}
	}
	return NULL;
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

DynamicTrace* DynamicTrace_create(uint32_t xTiles, uint32_t yTiles, uint32_t xSize, uint32_t ySize)
{
	DynamicTrace* dt = (DynamicTrace*)malloc(sizeof(DynamicTrace));
	if(dt == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}

	dt->xTiles = xTiles;
	dt->yTiles = yTiles;
	dt->xSize  = xSize;
	dt->ySize  = ySize;

	dt->tiles = (List***)malloc(sizeof(List**)*xTiles);
	uint32_t i, j;
	for(i=0; i < xTiles; i++)
	{
		dt->tiles[i] = (List**)malloc(sizeof(List*)*yTiles);
		for(j=0; j < yTiles; j++)
			dt->tiles[i][j] = List_create();
	}

	return dt;
}

void DynamicTrace_addTile(DynamicTrace* self, Tile* tile)
{
	Drawable* tileDrawable;
	const SDL_Rect* tileRect = Drawable_getRect(tileDrawable);
	uint32_t xIndice, yIndice;
	xIndice = tileRect->x / self->xSize;
	yIndice = tileRect->y / self->ySize;
	List_addData(self->tiles[xIndice][yIndice], (void*)tile);
}

void DynamicTrace_draw(DynamicTrace* self, Window* window)
{
	uint32_t i, j, k;
	for(i=0; i < self->xTiles; i++)
	{
		for(j=0; j < self->yTiles; j++)
		{
			for(k=0; k < List_getLen(self->tiles[i][j]); k++)
			{
				Tile* tile = (Tile*)List_getData(self->tiles[i][j], k);
				if(tile)
					((Drawable*)tile)->draw((Drawable*)tile, window);
			}
		}
	}
}

void DynamicTrace_destroy(DynamicTrace* self)
{
	uint32_t i, j, k;
	for(i=0; i < self->xTiles; i++)
	{
		for(j=0; j < self->yTiles; j++)
		{
			for(k=0; k < List_getLen(self->tiles[i][j]); k++)
			{
				Drawable* tile = List_getData(self->tiles[i][j], k);
				tile->destroy(tile);
			}
			List_destroy(self->tiles[i][j]);
		}
		free(self->tiles[i]);
	}
	free(self->tiles);
	free(self);
}
