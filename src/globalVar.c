#include "globalVar.h"

Window* globalVar_window = NULL;
ResourcesManager* globalVar_fonts = NULL;

SDL_Color RED = {.r=255, .g=0, .b=0};
SDL_Color GREEN = {.r=0, .g=255, .b=0};
SDL_Color BLUE = {.r=0, .g=0, .b=255};
SDL_Color MAGENTA = {.r=255, .g=0, .b=255};
SDL_Color YELLOW = {.r=255, .g=255, .b=0};
SDL_Color CYAN = {.r=0, .g=255, .b=255};
SDL_Color BLACK = {.r=0, .g=0, .b=0};
SDL_Color WHITE = {.r=255, .g=255, .b=255};

void globalVar_destroy()
{
	if(globalVar_window)
		Window_destroy(globalVar_window);
	if(globalVar_fonts)
		ResourcesManager_destroy(globalVar_fonts);
}
