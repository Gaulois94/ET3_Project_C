#ifndef  GAME_INC
#define  GAME_INC

#include "stdlib.h"
#include "Contexts/Context.h"
#include "Contexts/Option.h"
#include "Contexts/Start.h"
#include "SDL2/SDL.h"
#include "Player.h"
#include "Contexts/InGame.h"
#include "MusicManager.h"

typedef struct
{
	Context* currentContext;
	InGame* inGameContext;
	Option* optionContext;
	Start*  startContext;
	SDL_Event event;
	bool quit;
	bool finishLevel;
}Game;

Game* Game_create();
void  Game_run(Game* game);
void  Game_destroy();

#endif
