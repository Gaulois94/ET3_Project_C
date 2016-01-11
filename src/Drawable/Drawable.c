#include "Drawable/Drawable.h"

void Drawable_init(Drawable* self, const SDL_Rect* destRect)
{
	Active_init((Active*)self);
	self->draw = NULL;
	self->destroy = &Drawable_destroy;
	copyRect(&(self->rect), destRect);
}

void Drawable_draw(Drawable* self, SDL_Renderer* renderer)
{
	if(self->draw)
		self->draw(self, renderer);
}

const SDL_Rect* Drawable_getRect(Drawable* self)
{
	return &(self->rect);
}

void Drawable_setSize(Drawable* self, uint32_t width, uint32_t height)
{
	self->rect.w = width;
	self->rect.h = height;
}

void Drawable_setPosition(Drawable* self, int32_t x, int32_t y)
{
	self->rect.x = x;
	self->rect.y = y;
}

void copyRect(SDL_Rect* dest, const SDL_Rect* src)
{
	if(src == NULL)
	{
		dest->w = dest->h = 0;
		return;
	}

	dest->x = src->x;
	dest->y = src->y;
	dest->w = src->w;
	dest->h = src->h;
}

const SDL_Rect* evaluateRect(const SDL_Rect* rect)
{
	if(rect->w == 0 && rect->h == 0)
		return NULL;
	return rect;
}

void Drawable_destroy(Drawable* self)
{
	free(self);
}
