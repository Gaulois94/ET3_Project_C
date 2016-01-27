#ifndef  GLOBARVAR_INC
#define  GLOBARVAR_INC

#include "Window.h"
#include "ResourcesManager.h"
#include "MusicManager.h"

typedef enum
{
	NOTHING,
	START,
	INGAME,
	OPTION,
	QUIT
}EnumContext;

void globalVar_destroy();

bool rectCollision(const SDL_Rect* rect1, const SDL_Rect* rect2);

extern Window*           globalVar_window;
extern ResourcesManager* globalVar_fonts;
extern MusicManager*     globalVar_musics;

extern SDL_Color RED;
extern SDL_Color GREEN;
extern SDL_Color BLUE;
extern SDL_Color MAGENTA;
extern SDL_Color YELLOW;
extern SDL_Color CYAN;
extern SDL_Color BLACK;
extern SDL_Color WHITE;

extern uint32_t globalVar_jumpscancode;
extern uint32_t globalVar_leftscancode;
extern uint32_t globalVar_rightscancode;

#endif
