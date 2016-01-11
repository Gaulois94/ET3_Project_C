#include "globalVar.h"

Window* globalVar_window = NULL;
ResourcesManager* globalVar_fonts = NULL;

void globalVar_destroy()
{
	if(globalVar_window)
		Window_destroy(globalVar_window);
	if(globalVar_fonts)
		ResourcesManager_destroy(globalVar_fonts);
}
