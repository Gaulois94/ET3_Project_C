#include "Drawable/Drawable.h"

void Drawable_init(Drawable* self, const SDL_Rect* destRect)
{
	Active_init((Active*)self);
	self->draw = NULL;
	self->destroy = &Drawable_destroy;
	self->isStatic = false;
	self->setStatic = &Drawable_setStatic;
	self->setPosition = &Drawable_setPosition;
	self->setSize = &Drawable_setSize;
	copyRect(&(self->rect), destRect);
}

void Drawable_draw(Drawable* self, Window* window)
{
	if(self->draw)
		self->draw(self, window);
}

const SDL_Rect* Drawable_getRect(const Drawable* self)
{
	return &(self->rect);
}

bool Drawable_pointOnRect(const Drawable* self, const SDL_Point* p)
{
	return pointOnRect(&(self->rect), p);
}

bool Drawable_pointOnRectOnScreen(const Drawable* self, const Window* window, const SDL_Point* p)
{

	SDL_Rect rect = Drawable_getRectOnScreen(self, window);
	return pointOnRect(&rect, p);
}

SDL_Rect Drawable_getRectOnScreen(const Drawable* self, const Window* window)
{
	if(self->isStatic)
		return self->rect;
	SDL_Point p;
	SDL_Rect rect;
	rect.w = self->rect.w;
	rect.h = self->rect.h;
	p.x = self->rect.x;
	p.y = self->rect.y;

	p = Window_convertToScreenCoord(window, &p);
	rect.x = p.x;
	rect.y = p.y;
	return rect;
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

void Drawable_setStatic(Drawable* self, bool isStatic)
{
	self->isStatic = isStatic;
}

void Drawable_setRect(Drawable* self, const SDL_Rect* rect)
{
	self->setPosition(self, rect->x, rect->y);
	self->setSize(self, rect->x, rect->y);
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

void Drawable_move(Drawable* self, int32_t x, int32_t y)
{
	if(!self->setPosition)
	{
		self->rect.x += x;
		self->rect.y += y;
	}
	else
		self->setPosition(self, self->rect.x + x, self->rect.y + y);
}

bool pointOnRect(const SDL_Rect* rect, const SDL_Point* p)
{
	return (p->x >= rect->x && p->x <= rect->x + rect->w &&
			p->y >= rect->y && p->y <= rect->y + rect->h);
}
