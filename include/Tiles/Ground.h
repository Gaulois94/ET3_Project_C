#ifndef  GROUND_INC
#define  GROUND_INC

#include "Tiles/Tile.h"
#include "Drawable/Sprite.h"

typedef struct Ground
{
	Tile base;
}Ground;

Tile* Ground_create(SDL_Texture* texture, const SDL_Rect* subRect);
void    Ground_init(Ground* self, SDL_Texture* texture, const SDL_Rect* subRect);
uint32_t Ground_updateCollision(Tile* self);

#endif
