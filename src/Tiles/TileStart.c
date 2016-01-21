#include "Tiles/TileStart.h"

Tile* TileStart_create(SDL_Texture* texture, const SDL_Rect* subRect)
{
	TileStart* self = (TileStart*)malloc(sizeof(TileStart));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	TileStart_init(self, texture, subRect);
	return ((Tile*)self);
}

void TileStart_init(TileStart* self, SDL_Texture* texture, const SDL_Rect* subRect)
{
	Tile_init((Tile*)self, texture, subRect);
	((Tile*)self)->info = BEGIN;
}
