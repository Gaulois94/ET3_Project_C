#include "Widgets/Button.h"

Button* Button_create(void(*callback)(void*), void* data, const SDL_Rect* rect, Sprite* image, Text* text)
{
	Button* button = (Button*)malloc(sizeof(Button));
	if(button == NULL)
	{
		perror("Error on malloc");
		return NULL;
	}
	Button_init(button, callback, data, rect, image, text);
}

void Button_init(Button* self, void(*callback)(void*), void* data, const SDL_Rect* rect, Sprite* image, Text* text)
{

}

void Button_howActive(Active* self, const SDL_Event* event)
{

}

void Button_howDisactive(Active* self, const SDL_Event* event)
{

}

void Button_draw(Drawable* drawable, SDL_Renderer* renderer)
{
	Button* self = (Button*)drawable;
	if(self->sprite)
		Sprite_draw(((Drawable*)self->sprite), renderer);
	if(self->text)
		Text_draw(((Drawable*)self->text), renderer);
}

void Button_destroy(Button* self)
{
	Drawable_destroy((Drawable*)self);
}
