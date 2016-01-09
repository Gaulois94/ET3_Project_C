#include "Game.h"
#include "Window.h"

int main()
{
	Window_initSDL();

	Game* game = game_new();
	Game_run(game);

	Game_destroy(game);
	globalVar_destroy();

	return 0;
}
