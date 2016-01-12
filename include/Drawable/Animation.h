#ifndef  ANIMATION_INC
#define  ANIMATION_INC

#include "SDL2/SDL.h"
#include "Drawable/Sprite.h"

typedef struct Animation
{
	Sprite base;

	void(*setSubNSpriteRect)(struct Animation*, uint32_t);

	uint32_t maxN;
	uint32_t currentN;
	uint32_t iFrame;
	uint32_t nbFrame;

	bool inAnimation;
}Animation;

void Animation_init(Animation* self, const SDL_Rect* destRect, SDL_Texture* texture, uint32_t maxN, uint32_t currentN, uint32_t nbFrame);
void Animation_draw(Drawable* self, Window* window);

void Animation_setSubNSpriteRect(Animation* self, uint32_t n);
void Animation_setInAnimation(Animation* self, bool inAnimation, bool reset);
bool Animation_getInAnimation(const Animation* self);

#endif
