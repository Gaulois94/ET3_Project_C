#include "Tiles/Coin.h"

Tile* Coin_create(SDL_Texture* texture, const SDL_Rect* subRect)
{
	Coin* self = (Coin*)malloc(sizeof(Coin));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	Coin_init(self, texture, subRect);
	return (Tile*)self;
}

void Coin_init(Coin* self, SDL_Texture* texture, const SDL_Rect* subRect)
{
	Tile_init((Tile*)self, texture, subRect);
	((Tile*)self)->sprite          = Sprite_create(NULL, texture, subRect);
	((Tile*)self)->updateCollision = &Coin_updateCollision;
}

uint32_t Coin_updateCollision(Tile* self)
{
	return 0x00;
}
