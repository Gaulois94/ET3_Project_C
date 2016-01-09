#ifndef  GLOBARVAR_INC
#define  GLOBARVAR_INC

#include "Window.h"
#include "ResourcesManager.h"

typedef char bool;

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
