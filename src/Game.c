#include "Game.h"

Game* Game_create()
{
	Game* game = (Game*)malloc(sizeof(Game));
	game->currentContext = NULL;
	globalVar_window = Window_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Like");

	return game;
}

void Game_run(Game* game)
{
}

void Game_destroy(Game* game)
{
	free(game);
}
