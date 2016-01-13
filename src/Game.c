#include "Game.h"

Game* Game_create()
{
	Game* game = (Game*)malloc(sizeof(Game));
	game->currentContext = NULL;
	game->quit = false;
	globalVar_window = Window_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Like");

	return game;
}

void Game_run(Game* game)
{
	while(!game->quit)
	{
		while(SDL_PollEvent(&(game->event)))
		{
			if(game->event.type == SDL_QUIT)
			{
				game->quit = true;
				break;
			}
		}
		if(!game->quit)
		{

		}
	}
}

void Game_destroy(Game* game)
{
	free(game);
}
