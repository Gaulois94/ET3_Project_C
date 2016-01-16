#ifndef  DEFAULTTILE_INC
#define  DEFAULTTILE_INC

#include "Tiles/Tile.h"
#include "Drawable/Sprite.h"

typedef struct DefaultTile
{
	Tile base;
}DefaultTile;

Tile* DefaultTile_create(SDL_Texture* texture, const SDL_Rect* subRect);
void    DefaultTile_init(DefaultTile* self, SDL_Texture* texture, const SDL_Rect* subRect);
uint32_t DefaultTile_updateCollision(Tile* self);


#endif
