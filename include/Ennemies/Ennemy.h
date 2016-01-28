#ifndef  ENNEMY_INC
#define  ENNEMY_INC

#include "SDL2/SDL.h"
#include "Tiles/Tile.h"

typedef enum{DLEFT, DRIGHT}Direction;

typedef struct
{
	Tile base;
	float speedY;
	float moveX;
	Direction direction;
}Ennemy;

void Ennemy_init(Ennemy* self, SDL_Texture* texture, const SDL_Rect* subRect);

#endif
