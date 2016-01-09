#ifndef  GAME_INC
#define  GAME_INC

#include "stdlib.h"
#include "Contexts/Context.h"
#include "globalVar.h"
#include "SDL2/SDL.h"

typedef struct
{
	Context* currentContext;
	SDL_Event* event;
}Game;

Game* Game_create();
void  Game_run(Game* game);
void  Game_destroy();

#endif
