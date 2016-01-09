#ifndef  GLOBARVAR_INC
#define  GLOBARVAR_INC

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define FPS 60

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
extern ResourcesManager* globalVar_textures;
extern ResourcesManager* globalVar_fonts;

#endif
