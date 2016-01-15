#ifndef  CHECKBOX_INC
#define  CHECKBOX_INC

#include "Drawable/Drawable.h"

typedef struct
{
	Drawable base;
	SDL_Rect rect;
}CheckBox;

CheckBox* CheckBox_create(void(*callback)(void*), void* data, const SDL_Rect* rect);
void CheckBox_init(CheckBox* self, void(*callback)(void*), void* data, const SDL_Rect* rect);
bool CheckBox_howActive(Active* self, const SDL_Event* event);
bool CheckBox_howDisactive(Active* self, const SDL_Event* event);
void CheckBox_draw(Drawable* drawable, Window* window);

#endif
