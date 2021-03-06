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

	//Init the array for tiles and objects
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
	//Draw every tiles and objects
	uint32_t i, j;
	for(i=0; i < self->nbCasesX; i++)
	{
		for(j=0; j < self->nbCasesY; j++)
		{
			//If it exists
			if(self->tiles[i][j])
			{
				//Destroy it if needed
				if(self->tiles[i][j]->canDestroy)
				{
					((Drawable*)self->tiles[i][j])->destroy((Drawable*)(self->tiles[i][j]));
					self->tiles[i][j] = NULL;
				}
				//Else draw it
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
	//if the position is correct
	if(x < self->nbCasesX && y < self->nbCasesY && tile)
	{
		//Add the tile
		self->tiles[x][y] = tile;

		//And set its position
		Drawable* tileDrawable = (Drawable*)tile;
		tileDrawable->setPosition(tileDrawable, self->padX + x*self->sizeX, self->padY + y*self->sizeY);
	}
}

void StaticTrace_addObject(StaticTrace* self, Object* object, uint32_t x, uint32_t y)
{
	//Same that addTiles but for object
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
	//Need to look for every object from 0 to indiceX / Y
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

DynamicTrace* DynamicTrace_create(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY)
{
	DynamicTrace* dt = (DynamicTrace*)malloc(sizeof(DynamicTrace));
	if(dt == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}

	dt->nbCasesX = nbCasesX;
	dt->nbCasesY = nbCasesY;
	dt->sizeX  = sizeX;
	dt->sizeY  = sizeY;

	dt->tiles = (List***)malloc(sizeof(List**)*nbCasesX);
	uint32_t i, j;
	for(i=0; i < nbCasesX; i++)
	{
		dt->tiles[i] = (List**)malloc(sizeof(List*)*nbCasesY);
		for(j=0; j < nbCasesY; j++)
			dt->tiles[i][j] = List_create();
	}

	return dt;
}

void DynamicTrace_addTile(DynamicTrace* self, Tile* tile)
{
	Drawable* tileDrawable;
	//Add the tile to a List following its position
	const SDL_Rect* tileRect = Drawable_getRect(tileDrawable);
	uint32_t xIndice, yIndice;
	xIndice = tileRect->x / self->sizeX;
	yIndice = tileRect->y / self->sizeY;
	if(xIndice < self->nbCasesX && yIndice < self->nbCasesY)
		List_addData(self->tiles[xIndice][yIndice], (void*)tile);
}

Tile* DynamicTrace_getTile(DynamicTrace* self, uint32_t x, uint32_t y)
{
	uint32_t i, j;
	uint32_t xIndice, yIndice;
	xIndice = x / self->sizeX;
	yIndice = y / self->sizeY;
	List* dynamicList[4]={NULL, NULL, NULL, NULL};

	//Because the tile isn't in an absolute position, we need to check on 4 list if we have something on this position
	//This is faster than searching for all the tiles is it in collision with the position x, y
	if(xIndice < self->nbCasesX && yIndice < self->nbCasesY)
		dynamicList[0] = self->tiles[xIndice][yIndice];
	if(xIndice-1 < self->nbCasesX && xIndice > 0 && yIndice < self->nbCasesY)
		dynamicList[1] = self->tiles[xIndice-1][yIndice];
	if(xIndice < self->nbCasesX && yIndice -1 < self->nbCasesY && yIndice > 0)
		dynamicList[2] = self->tiles[xIndice][yIndice-1];
	if(xIndice-1 < self->nbCasesX && xIndice > 0 && yIndice -1 < self->nbCasesY && yIndice > 0)
		dynamicList[3] = self->tiles[xIndice-1][yIndice-1];

	for(i=0; i < 4; i++)
	{
		if(dynamicList[i])
		{
			for(j=0; j < List_getLen(dynamicList[i]); j++)
			{
				SDL_Point p;
				p.x = x;
				p.y = y;
				Tile* tile = (Tile*)List_getData(dynamicList[i], j);
				if(tile)
				{
					if(pointOnRect(Drawable_getRect((Drawable*)tile), &p))
						return tile;
				}
			}
		}
	}

	return NULL;
}

void DynamicTrace_draw(DynamicTrace* self, Window* window)
{
	uint32_t i, j, k;
	//Draw everything
	for(i=0; i < self->nbCasesX; i++)
	{
		for(j=0; j < self->nbCasesY; j++)
		{
			for(k=0; k < List_getLen(self->tiles[i][j]); k++)
			{
				Tile* tile = (Tile*)List_getData(self->tiles[i][j], k);
				if(tile)
				{
					//and destroy it if needed
					if(tile->canDestroy)
					{
						List_removeData(self->tiles[i][j], (void*)tile);
						((Drawable*)tile)->destroy((Drawable*)tile);
					}

					else
					{ 
						if(tile->hasMove)
						{
							List_removeData(self->tiles[i][j], (void*)tile);
							const SDL_Rect* tileRect = Drawable_getRect((Drawable*)tile);
							uint32_t xIndice, yIndice;
							xIndice = tileRect->x / self->sizeX;
							yIndice = tileRect->y / self->sizeY;

							if(xIndice < self->nbCasesX && yIndice < self->nbCasesY)
								List_addData(self->tiles[xIndice][yIndice], tile);

							tile->hasMove = false;
						}
						((Drawable*)tile)->draw((Drawable*)tile, window);
					}

				}
			}
		}
	}
}

List* DynamicTrace_getList(DynamicTrace* self, uint32_t x, uint32_t y)
{
	uint32_t xIndice, yIndice;
	xIndice = x / self->sizeX;
	yIndice = y / self->sizeY;
	if(xIndice < self->nbCasesX && yIndice < self->nbCasesY)
		return self->tiles[xIndice][yIndice];
	return NULL;
}

void DynamicTrace_destroy(DynamicTrace* self)
{
	uint32_t i, j, k;
	for(i=0; i < self->nbCasesX; i++)
	{
		for(j=0; j < self->nbCasesY; j++)
		{
			for(k=0; k < List_getLen(self->tiles[i][j]); k++)
			{
				Drawable* tile = List_getData(self->tiles[i][j], k);
				if(tile)
					tile->destroy(tile);
			}
			List_destroy(self->tiles[i][j]);
		}
		free(self->tiles[i]);
	}
	free(self->tiles);
	free(self);
}
