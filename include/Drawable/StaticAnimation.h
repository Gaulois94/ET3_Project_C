#ifndef  STATICANIMATION_INC
#define  STATICANIMATION_INC

#include "Drawable/Animation.h"

typedef struct
{
	Animation base;

	uint32_t posX, posY, padX, padY, width, height, nX;
}StaticAnimation;

StaticAnimation* StaticAnimation_create(const SDL_Rect* dest, SDL_Texture* texture, uint32_t posX, uint32_t posY, uint32_t padX, uint32_t padY, uint32_t width, uint32_t height, uint32_t nX, uint32_t nMax, uint32_t currentN, uint32_t nbFrame);

void StaticAnimation_init(StaticAnimation* self, const SDL_Rect* dest, SDL_Texture* texture, uint32_t posX, uint32_t posY, uint32_t padX, uint32_t padY, uint32_t width, uint32_t height, uint32_t nX, uint32_t nMax, uint32_t currentN, uint32_t nbFrame);

void StaticAnimation_setSubNSpriteRect(Animation* self, uint32_t n);

#endif
