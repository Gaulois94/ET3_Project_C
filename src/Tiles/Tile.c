#include "Tiles/Tile.h"

void Tile_init(Tile* self, SDL_Texture* texture, const SDL_Rect* rect)
{
	Drawable* drawable = (Drawable*)self;
	Drawable_init(drawable, rect);
	drawable->draw = &Tile_draw;
	drawable->setStatic = &Tile_setStatic;
	drawable->destroy = &Tile_destroy;
	drawable->setPosition = &Tile_setPosition;
	drawable->setSize = &Tile_setSize;

	self->solid      = true;
	self->doDamages  = false;
	self->sprite     = NULL;
	self->updateCollision = &Tile_updateCollision;
	self->info       = 0x00;
	self->canDestroy = false;

	self->update = NULL;
	self->data   = NULL;
	self->hasMove = false;
	self->hasDraw = false;
}

void Tile_setPosition(Drawable* drawable, int32_t x, int32_t y)
{
	Tile* self = (Tile*)drawable;
	if(self->sprite != NULL)
		((Drawable*)self->sprite)->setPosition(((Drawable*)self->sprite), x, y);
	Drawable_setPosition(drawable, x, y);
	self->hasMove = true;
}

void Tile_setSize(Drawable* drawable, uint32_t width, uint32_t height)
{
	Tile* self = (Tile*)drawable;
	if(self->sprite != NULL)
		((Drawable*)self->sprite)->setSize(((Drawable*)self->sprite), width, height);
	Drawable_setSize(drawable, width, height);
}

void Tile_setStatic(Drawable* drawable, bool s)
{
	Tile* self = (Tile*)drawable;
	if(self->sprite == NULL)
		return;
	((Drawable*)self->sprite)->setStatic(((Drawable*)self->sprite), s);
	Drawable_setStatic(drawable, s);
}

void Tile_draw(Drawable* drawable, Window* window)
{
	Tile* self = (Tile*)drawable;
	if(self->update)
		self->update(self, self->data);
	if(self->sprite == NULL)
		return;
	const SDL_Rect* rect = Drawable_getRect((Drawable*)self->sprite);
	((Drawable*)self->sprite)->draw(((Drawable*)self->sprite), window);
	self->hasDraw = true;
}

void Tile_destroy(Drawable* drawable)
{
	Tile* self = (Tile*)drawable;
	if(self->sprite != NULL)
		((Drawable*)self->sprite)->destroy(((Drawable*)self->sprite));
	Drawable_destroy(drawable);
}

uint32_t  Tile_getInfo(Tile* self)
{
	return self->info;
}

void Tile_setUpdate(Tile* self, void(*update)(Tile*, void*), void* data)
{
	self->update = update;
	self->data   = data;
}

uint32_t Tile_updateCollision(Tile* self)
{
	return self->info;
}
