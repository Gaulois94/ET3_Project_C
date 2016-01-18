#include "Game.h"
#include "Window.h"

int main()
{
	Window_initSDL();

	Game* game = Game_create();
	Game_run(game);

	Game_destroy(game);
	globalVar_destroy();
	Window_finishSDL();

	return 0;
}
