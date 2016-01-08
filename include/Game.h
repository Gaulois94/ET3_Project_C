#ifndef  GAME_INC
#define  GAME_INC

#include "stdlib.h"
#include "Context.h"
#include "SDL2/SDL.h"

typedef struct
{
	Context* currentContext;
}Game;

Game* Game_new();
void  Game_run(Game* game);
int   Game_initVideo(Game* game);
void  Game_fpsManager(Game* game);
void  Game_destroy();

#endif
