#ifndef  ELEMENT_INC
#define  ELEMENT_INC

#include "SDL2/SDL.h"

typedef struct
{
	SDL_Rect   rect;
	Animation* animation;
}Element;

#endif
