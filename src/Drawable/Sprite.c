#include "Sprite.h"

Sprite* Sprite_create(const SDL_Rect* destRect, const SDL_Texture* texture, const SDL_Rect* subRect)
{
	Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));
	Sprite_init(sprite, destRect, texture, subRect);
}

void Sprite_init(Sprite* self, const SDL_Rect* destRect, const SDL_Texture* texture, const SDL_Rect* subRect);
{
	Drawable_init((Drawable*)self, destRect);
	self->base->draw = &Sprite_draw;
	self->texture = texture;
	copyRect(&(self->subRect), subRect);
}

void Sprite_draw(Drawable* self, SDL_Renderer* renderer)
{
	Sprite* sprite = (Sprite*)self;
	SDL_RenderCopy(renderer, sprite->texture, evaluateRect(&(sprite->subRect)), Drawable_getRect((Drawable*)sprite));
}

const SDL_Rect* Sprite_getSubRect(Sprite* self)
{
	return &(self->subRect);
}

void Sprite_setSubRect(Sprite* self, SDL_Rect* subRect)
{
	copyRect(&(self->subRect), subRect);
}

void Sprite_destroy(Sprite* self)
{
	free(self);
}
