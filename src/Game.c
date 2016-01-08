#include "Game.h"

Game* Game_new()
{
	Game* game = (Game*)malloc(sizeof(Game));
	game->timer = 0;
	game->event;
	game->windowSurface = NULL;
	game->windowRenderer = NULL;

	Game_initVideo(game);

	return game;
}

void Game_run(Game* game)
{
}

void Game_destroy(Game* game)
{
	free(game);
}

void Game_fpsManager(Game* game)
{
	SDL_Delay(fmax(0, (float)(1.0/FPS) * 1000 - (SDL_GetTicks() - game->timer)));
	game->timer = SDL_GetTicks();
}

int Game_initVideo(Game* game)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
		return 0;
	}

	game->window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(game->window == NULL)
	{
		printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
		return 0;
	}

/*  if(TTF_Init() == -1)
    {
        return 0;    
    }*/
	return 1;
}
