#include "Game.h"

Game* Game_create()
{
	Game* game = (Game*)malloc(sizeof(Game));
	globalVar_window = Window_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Like");
	globalVar_fonts = ResourcesManager_create();
	game->currentContext = NULL;
	game->quit = false;
	TTF_Font* font = TTF_OpenFont("Resources/DejaVuSansMono.ttf", 15);
	if(font == NULL)
	{
		InGame_destroy(game->inGameContext);
		free(game);
		return NULL;
	}
	ResourcesManager_addData(globalVar_fonts, "dejavu", font);

	game->inGameContext  = InGame_create();
	game->optionContext  = Option_create();
	game->startContext   = Start_create();
	game->currentContext = (Context*)(game->startContext);


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

			if(game->currentContext)
				game->currentContext->updateEvent(game->currentContext, &(game->event));
		}



		if(!game->quit)
		{
			Window_clear(globalVar_window);
			if(game->currentContext)
			{
				switch(game->currentContext->run(game->currentContext))
				{
					case INGAME:
						game->currentContext = (Context*)(game->inGameContext);
						game->currentContext->reinit(game->currentContext);
						break;
					case START:
						game->currentContext = (Context*)(game->startContext);
						game->currentContext->reinit(game->currentContext);
						break;
					case OPTION:
						break;
					case QUIT:
						game->quit = true;
						break;
				}
			}
			Window_display(globalVar_window);
		}
	}
}

void Game_destroy(Game* game)
{
	InGame_destroy(game->inGameContext);
	free(game);
}
