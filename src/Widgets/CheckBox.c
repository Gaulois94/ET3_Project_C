#include "Widgets/CheckBox.h"

CheckBox* CheckBox_create(void(*callback)(void*), void* data, const SDL_Rect* rect)
{
	CheckBox* checkbox = (CheckBox*)malloc(sizeof(CheckBox));
	if(checkbox == NULL)
	{
		perror("Error on malloc");
		return NULL;
	}
	CheckBox_init(checkbox, callback, data, rect);
	return checkbox;
}

void CheckBox_init(CheckBox* self, void(*callback)(void*), void* data, const SDL_Rect* rect)
{
	Drawable_init((Drawable*)self, rect);
	((Active*)self)->howActive = &CheckBox_howActive;
	((Active*)self)->howDisactive = &CheckBox_howDisactive;
	((Drawable*)self)->draw = &CheckBox_draw;
}

bool CheckBox_howActive(Active* self, const SDL_Event* event)
{
	if(self->isActive == true)
		return false;

	if(event->type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_Point p;
		p.x = event->button.x;
		p.y = event->button.y;
		if(Drawable_pointOnRect((Drawable*)self, &p))
		return true;
	}
	return false;
}

bool CheckBox_howDisactive(Active* self, const SDL_Event* event)
{
	if(self->isActive == false)
		return false;

	if(event->type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_Point p;
		p.x = event->button.x;
		p.y = event->button.y;
		if(Drawable_pointOnRect((Drawable*)self, &p))
		return true;
	}
	return false;
}

void CheckBox_draw(Drawable* drawable, Window* window)
{
	CheckBox* self = (CheckBox*)drawable;
	SDL_Rect rect = Drawable_getRectOnScreen(drawable, window);
	SDL_SetRenderDrawColor(window->renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderFillRect(window->renderer, &rect);

	if(((Active*)self)->isActive)
	{
		SDL_SetRenderDrawColor(window->renderer, 0xff, 0x00, 0x00, 0xff);
		SDL_RenderDrawLine(window->renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
		SDL_RenderDrawLine(window->renderer, rect.x, rect.y + rect.h, rect.x + rect.w, rect.y);
	}
}
