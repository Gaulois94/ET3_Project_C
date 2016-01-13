#include "Drawable/Sprite.h"

Sprite* Sprite_create(const SDL_Rect* destRect, SDL_Texture* texture, const SDL_Rect* subRect)
{
	Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));
	Sprite_init(sprite, destRect, texture, subRect);
}

void Sprite_init(Sprite* self, const SDL_Rect* destRect, SDL_Texture* texture, const SDL_Rect* subRect)
{
	Drawable_init((Drawable*)self, destRect);
	self->autoSize = true;
	((Drawable*)self)->draw = &Sprite_draw;
	self->texture = texture;
	copyRect(&(self->subRect), subRect);
}

void Sprite_draw(Drawable* self, Window* window)
{
	Sprite* sprite = (Sprite*)self;
	SDL_Rect rect = Drawable_getRectOnScreen((Drawable*)sprite, window);
	SDL_RenderCopy(window->renderer, sprite->texture, evaluateRect(&(sprite->subRect)), &rect);
}

const SDL_Rect* Sprite_getSubRect(const Sprite* self)
{
	return &(self->subRect);
}

void Sprite_setSubRect(Sprite* self, SDL_Rect* subRect)
{
	copyRect(&(self->subRect), subRect);
	if(self->autoSize)
		Drawable_setRect((Drawable*)self, subRect);
}
