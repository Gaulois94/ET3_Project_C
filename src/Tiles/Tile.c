#include "Tiles/Tile.h"

void Tile_init(Tile* self, const SDL_Rect* destRect)
{
	Drawable* drawable = (Drawable*)self;
	Drawable_init(drawable, destRect);
	drawable->draw = &Tile_draw;
	drawable->setStatic = &Tile_setStatic;
	drawable->destroy = &Tile_destroy;
	drawable->setPosition = &Tile_setPosition;
	drawable->setSize = &Tile_setSize;

	self->solid = true;
	self->doDamages = false;
	drawable->setPosition(drawable, destRect->x, destRect->y);
	drawable->setSize(drawable, destRect->w, destRect->h);
}

void Tile_setPosition(Drawable* drawable, int32_t x, int32_t y)
{
	Tile* self = (Tile*)drawable;
	if(self->drawable == NULL)
		return;
	self->drawable->setPosition(self->drawable, x, y);
	Drawable_setPosition(drawable, x, y);
}

void Tile_setSize(Drawable* drawable, uint32_t width, uint32_t height)
{
	Tile* self = (Tile*)drawable;
	if(self->drawable == NULL)
		return;
	self->drawable->setSize(self->drawable, width, height);
	Drawable_setSize(drawable, width, height);
}

void Tile_setStatic(Drawable* drawable, bool s)
{
	Tile* self = (Tile*)drawable;
	if(self->drawable == NULL)
		return;
	self->drawable->setStatic(self->drawable, s);
	Drawable_setStatic(drawable, s);
}

void Tile_draw(Drawable* drawable, Window* window)
{
	Tile* self = (Tile*)drawable;
	if(self->drawable == NULL)
		return;
	self->drawable->draw(self->drawable, window);
}

void Tile_destroy(Drawable* drawable)
{
	Tile* self = (Tile*)drawable;
	if(self->drawable == NULL)
		return;
	self->drawable->destroy(self->drawable);
}
