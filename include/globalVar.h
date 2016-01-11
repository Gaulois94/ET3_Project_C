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

#endif
