#include "Drawable/DynamicAnimation.h"

DynamicAnimation* DynamicAnimation_create(const SDL_Rect* dest, const SDL_Texture* texture, const SDL_Rect* rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame)
{
	DynamicAnimation* self = (DynamicAnimation*)malloc(sizeof(DynamicAnimation));
	if(self == NULL)
	{
		perror("Error in malloc");
		return NULL;
	}
	((Drawable*)self)->destroy = &DynamicAnimation_destroy;
	DynamicAnimation_init(self, dest, texture, rectAnimation, maxN, currentN, nbFrame);
	return self;
}

void DynamicAnimation_init(DynamicAnimation* self, const SDL_Rect* dest, const SDL_Texture* texture, const SDL_Rect* rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame)
{
	Animation_init((Animation*)self, dest, texture, maxN, currentN, nbFrame);
	self->rect = (SDL_Rect*)malloc(maxN * sizeof(SDL_Rect));
	uint32_t i;
	for(i=0; i < maxN; i++)
		copyRect(&(self->rect[i]), &(rectAnimation[i]));
    ((Animation*)self)->setSubNSpriteRect = &DynamicAnimation_setSubNSpriteRect;
	((Animation*)self)->setSubNSpriteRect((Animation*)self, currentN);
}

void DynamicAnimation_setSubNSpriteRect(Animation* self, uint32_t n)
{
	DynamicAnimation* anim = (DynamicAnimation*)self;
	Sprite_setSubRect((Sprite*)anim, &(anim->rect[n]));
}

void DynamicAnimation_destroy(Drawable* self)
{
	DynamicAnimation* da = (DynamicAnimation*)self;
	if(self)
		if(da->rect != NULL)
			free(da->rect);
	Drawable_destroy(self);
}
