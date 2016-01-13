#ifndef  SPRITE_INC
#define  SPRITE_INC

#include "Drawable.h"

typedef struct Sprite
{
	Drawable base;
	SDL_Texture* texture;
	SDL_Rect subRect;
	bool autoSize;
}Sprite;

Sprite*         Sprite_create(const SDL_Rect* destRect, SDL_Texture* texture, const SDL_Rect* subRect);
void            Sprite_init(Sprite* self, const SDL_Rect* destRect, SDL_Texture* texture, const SDL_Rect* subRect);

void            Sprite_draw(Drawable* self, Window* window);

const SDL_Rect* Sprite_getSubRect(const Sprite* self);
void            Sprite_setSubRect(Sprite* self, SDL_Rect* subRect);

#endif
