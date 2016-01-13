#include "Game.h"
#include "Window.h"

int main()
{
	Window_initSDL();

	Game* game = Game_create();
	Game_run(game);

	Game_destroy(game);
	printf("Game destroyed \n");
	globalVar_destroy();
	printf("globalVar_destroy \n");
	Window_finishSDL();
	printf("finish SDL");

	return 0;
}
