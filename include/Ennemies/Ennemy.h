#ifndef  ENNEMY_INC
#define  ENNEMY_INC

#include "SDL2/SDL.h"
#include "Tiles/Tile.h"

typedef struct
{
	Tile base;
}Ennemy;

void Ennemy_init(Ennemy* self, SDL_Texture* texture, const SDL_Rect* subRect);

#endif
