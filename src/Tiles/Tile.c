#include "Tiles/Tile.h"

void Tile_init(Tile* self, SDL_Texture* texture, const SDL_Rect* subRect)
{
	Drawable* drawable = (Drawable*)self;
	Drawable_init(drawable, NULL);
	drawable->draw = &Tile_draw;
	drawable->setStatic = &Tile_setStatic;
	drawable->destroy = &Tile_destroy;
	drawable->setPosition = &Tile_setPosition;
	drawable->setSize = &Tile_setSize;

	self->solid      = true;
	self->doDamages  = false;
	self->sprite     = NULL;
	self->info       = 0x00;
	self->canDestroy = false;
}

void Tile_setPosition(Drawable* drawable, int32_t x, int32_t y)
{
	Tile* self = (Tile*)drawable;
	if(self->sprite == NULL)
		return;
	((Drawable*)self->sprite)->setPosition(((Drawable*)self->sprite), x, y);
	Drawable_setPosition(drawable, x, y);
}

void Tile_setSize(Drawable* drawable, uint32_t width, uint32_t height)
{
	Tile* self = (Tile*)drawable;
	if(self->sprite == NULL)
		return;
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
	if(self->sprite == NULL)
		return;
	const SDL_Rect* rect = Drawable_getRect((Drawable*)self->sprite);
	((Drawable*)self->sprite)->draw(((Drawable*)self->sprite), window);
}

void Tile_destroy(Drawable* drawable)
{
	Tile* self = (Tile*)drawable;
	if(self->sprite != NULL)
		((Drawable*)self->sprite)->destroy(((Drawable*)self->sprite));
	Drawable_destroy(drawable);
}

uint32_t  Tile_getInfo(Tile* tile)
{
	return tile->info;
}
