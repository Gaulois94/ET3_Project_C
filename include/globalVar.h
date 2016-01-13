#ifndef  GLOBARVAR_INC
#define  GLOBARVAR_INC

#include "Window.h"
#include "ResourcesManager.h"

typedef enum
{
	NOTHING,
	INGAME,
	OPTION,
	QUIT
}EnumContext;

void globalVar_destroy();

extern Window*           globalVar_window;
extern ResourcesManager* globalVar_fonts;

extern SDL_Color RED;
extern SDL_Color GREEN;
extern SDL_Color BLUE;
extern SDL_Color MAGENTA;
extern SDL_Color YELLOW;
extern SDL_Color CYAN;
extern SDL_Color BLACK;
extern SDL_Color WHITE;

#endif
