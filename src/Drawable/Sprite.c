#include "Drawable/Sprite.h"

Sprite* Sprite_create(const SDL_Rect* destRect, SDL_Texture* texture, const SDL_Rect* subRect)
{
	Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));
	if(sprite == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	Sprite_init(sprite, destRect, texture, subRect);
	return sprite;
}

void Sprite_init(Sprite* self, const SDL_Rect* destRect, SDL_Texture* texture, const SDL_Rect* subRect)
{
	Drawable_init((Drawable*)self, destRect);
	self->autoSize = true;
	((Drawable*)self)->draw = &Sprite_draw;
	self->texture = texture;
	Sprite_setSubRect(self, subRect);
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

void Sprite_setSubRect(Sprite* self, const SDL_Rect* subRect)
{
	if(subRect == NULL )
	{
		if(self->texture == NULL)
			return;
		uint32_t w, h;
		SDL_QueryTexture(self->texture, NULL, NULL, &w, &h);
		SDL_Rect sR;
		sR.x = 0;
		sR.y = 0;
		sR.w = 0;
		sR.h = 0;
		copyRect(&(self->subRect), &sR);
		Drawable_setSize((Drawable*)self, w, h);
	}
	else
	{
		copyRect(&(self->subRect), subRect);
		if(self->autoSize)
			Drawable_setSize((Drawable*)self, subRect->w, subRect->h);
	}
}
