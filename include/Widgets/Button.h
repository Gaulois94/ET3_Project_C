#ifndef  BUTTON_INC
#define  BUTTON_INC

#include "Drawable/Sprite.h"

typedef struct
{
	Drawable base;
	Sprite* image;
	Text*   text;
}Button;

Button* Button_create(void(*callback)(void*), void* data, const SDL_Rect* rect, Sprite* image, Text* text);
void Button_init(Button* self, void(*callback)(void*), void* data, const SDL_Rect* rect, Sprite* image, Text* text);
void Button_draw(Drawable* drawable, SDL_Renderer* renderer)
void Button_destroy(Button* self);

#endif
