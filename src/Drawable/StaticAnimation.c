#include "Drawable/StaticAnimation.h"

StaticAnimation* StaticAnimation_create(const SDL_Rect* dest, SDL_Texture* texture, uint32_t posX, uint32_t posY, uint32_t padX, uint32_t padY, uint32_t width, uint32_t height, uint32_t nX, uint32_t maxN, uint32_t currentN, uint32_t nbFrame)
{
	StaticAnimation* self = (StaticAnimation*)malloc(sizeof(StaticAnimation));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}

	StaticAnimation_init(self, dest, texture, posX, posY, padX, padY, width, height, nX, maxN, currentN, nbFrame);
	return self;
}

void StaticAnimation_init(StaticAnimation* self, const SDL_Rect* dest, SDL_Texture* texture, uint32_t posX, uint32_t posY, uint32_t padX, uint32_t padY, uint32_t width, uint32_t height, uint32_t nX, uint32_t maxN, uint32_t currentN, uint32_t nbFrame)
{
	Animation_init((Animation*)self, dest, texture, maxN, currentN, nbFrame);
	self->posX   = posX;
	self->posY   = posY;
	self->padX   = padX;
	self->padY   = padY;

	self->width  = width;
	self->height = height;
	self->nX     = nX;

    ((Animation*)self)->setSubNSpriteRect = &StaticAnimation_setSubNSpriteRect;
	((Animation*)self)->setSubNSpriteRect((Animation*)self, currentN);
}

void StaticAnimation_setSubNSpriteRect(Animation* self, uint32_t n)
{
    StaticAnimation* anim = (StaticAnimation*)self;

    SDL_Rect rect;
    rect.x = anim->posX + (anim->padX + anim->width) * (n%anim->nX);
    rect.y = anim->posY + (anim->padY + anim->height)*(n/anim->nX);
    rect.w = anim->width;
    rect.h = anim->height;

    Sprite_setSubRect((Sprite*)self, &rect);
}
