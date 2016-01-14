#include "Tiles/Ground.h"

Tile* Ground_create()
{
	Ground* self = (Ground*)malloc(sizeof(Ground));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	Ground_init(self);
	return (Tile*)self;
}

void Ground_init(Ground* self)
{
	Tile_init((Tile*)self, NULL);
	((Tile*)(self))->updateCollision = &Ground_updateCollision;
}

uint32_t Ground_updateCollision(Tile* self)
{
	return 0x00;
}
