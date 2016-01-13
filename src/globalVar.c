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
	{
		int32_t i;
		int32_t len = ResourcesManager_getLen(globalVar_fonts);
		for(i=len-1; i >= 0; i--)
			TTF_CloseFont((TTF_Font*)(ResourcesManager_getDataByID(globalVar_fonts, i)));
		ResourcesManager_destroy(globalVar_fonts);
	}
}
