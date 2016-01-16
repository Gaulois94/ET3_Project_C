#include "Tiles/DefaultTile.h"

Tile* DefaultTile_create(SDL_Texture* texture, const SDL_Rect* subRect)
{
	DefaultTile* tile = (DefaultTile*)malloc(sizeof(Tile));
	if(tile == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	DefaultTile_init(tile, texture, subRect);
	return (Tile*)tile;
}

void DefaultTile_init(DefaultTile* self, SDL_Texture* texture, const SDL_Rect* subRect)
{
	Tile_init((Tile*)self, texture, subRect);
	((Tile*)self)->sprite          = Sprite_create(NULL, texture, subRect);
	((Tile*)self)->updateCollision = &DefaultTile_updateCollision;
}

uint32_t DefaultTile_updateCollision(Tile* self)
{
	return 0x00;
}
