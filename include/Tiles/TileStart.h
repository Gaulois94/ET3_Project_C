#ifndef  TILESTART_INC
#define  TILESTART_INC

#include "Tiles/Tile.h"

typedef struct
{
	Tile base;
}TileStart;

Tile* TileStart_create(SDL_Texture* texture, const SDL_Rect* subRect);
void  TileStart_init(TileStart* self, SDL_Texture* texture, const SDL_Rect* subRect);

#endif
