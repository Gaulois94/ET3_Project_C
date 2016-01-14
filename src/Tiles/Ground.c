#include "Tiles/Ground.h"

Ground* Ground_create(const SDL_Rect* destRect)
{
	Ground* self = (Ground*)malloc(sizeof(Ground));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	Ground_init(self, destRect);
}

void Ground_init(Ground* self, const SDL_Rect* destRect)
{
	Tile_init((Tile*)self, destRect);
	((Tile*)(self))->updateCollision = &Ground_updateCollision;
}

uint32_t Ground_updateCollision(Ground* self)
{
	return 0x00;
}
