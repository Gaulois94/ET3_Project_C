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
	uint32_t i=0;
	for(i=0; i < nbCasesX; i++)
		self->tiles[i] = (Tile**)malloc(nbCasesY * sizeof(Tile*));

	return self;
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
				tile->destroy(tile);
			}
		}
		free(self->tiles[i]);
	}
	free(self->tiles);
	free(self);
}
