#include "Game.h"

int main()
{
	Game* game = game_new();
	game_run(game);
	game_destroy(game);

	return 0;
}
