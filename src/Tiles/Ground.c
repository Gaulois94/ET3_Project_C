#include "Tiles/Ground.h"

Tile* Ground_create(SDL_Texture* texture, const SDL_Rect* subRect)
{
	Ground* self = (Ground*)malloc(sizeof(Ground));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	Ground_init(self, texture, subRect);
	return ((Tile*)self);
}

void Ground_init(Ground* self, SDL_Texture* texture, const SDL_Rect* subRect)
{
	Tile_init((Tile*)self, texture, subRect);
	((Tile*)self)->sprite          = Sprite_create(NULL, texture, subRect);
	((Tile*)self)->updateCollision = &Ground_updateCollision;
}

uint32_t Ground_updateCollision(Tile* self)
{
	return 0x00;
}
