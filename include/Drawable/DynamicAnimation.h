#ifndef  DYNAMICANIMATION_INC
#define  DYNAMICANIMATION_INC

#include "Drawable/Animation.h"

typedef struct
{
	Animation base;
	SDL_Rect* rect;
}DynamicAnimation;

DynamicAnimation* DynamicAnimation_create(const SDL_Rect* dest, const SDL_Texture* texture, const SDL_Rect* rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame);
void DynamicAnimation_init(DynamicAnimation* self, const SDL_Rect* dest, const SDL_Texture* texture, const SDL_Rect* rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame);
void DynamicAnimation_setSubNSpriteRect(Animation* self, uint32_t n);
void DynamicAnimation_destroy(Drawable* self);

#endif
