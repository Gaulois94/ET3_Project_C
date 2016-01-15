#ifndef  COIN_INC
#define  COIN_INC

#include "Tiles/Tile.h"

typedef struct 
{
	Tile base;
}Coin;

Tile* Coin_create(SDL_Texture* texture, const SDL_Rect* subRect);
void Coin_init(Coin* self, SDL_Texture* texture, const SDL_Rect* subRect);
uint32_t Coin_updateCollision(Tile* self);

#endif
