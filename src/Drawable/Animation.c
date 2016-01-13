#include "Drawable/Animation.h"

void Animation_init(Animation* self, const SDL_Rect* destRect, SDL_Texture* texture, uint32_t maxN, uint32_t currentN, uint32_t nbFrame)
{
	Sprite_init((Sprite*)self, destRect, texture, NULL);
	((Drawable*)self)->draw = &Animation_draw;

	self->setSubNSpriteRect = &Animation_setSubNSpriteRect;
	self->maxN = maxN;
	self->currentN = currentN;
	self->nbFrame = nbFrame;
	self->iFrame = 0;
	self->inAnimation = true;
}

void Animation_draw(Drawable* drawable, Window* window)
{
	Animation* self = (Animation*)drawable;
	if(self->inAnimation)
	{
		if(self->iFrame == self->nbFrame)
		{
			self->iFrame = 0;
			self->currentN = (self->currentN+1) % self->maxN;
			self->setSubNSpriteRect(self, self->currentN);
		}
		else
			self->iFrame++;
	}

	Sprite_draw((Drawable*)self, window);
}

void Animation_setSubNSpriteRect(Animation* self, uint32_t n)
{
}

void Animation_setInAnimation(Animation* self, bool inAnimation, bool reset)
{
	if(reset)
		self->iFrame = 0;
	self->inAnimation = inAnimation;
}

bool Animation_getInAnimation(const Animation* self)
{
	return self->inAnimation;
}
