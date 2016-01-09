#ifndef  SPRITE_INC
#define  SPRITE_INC

#include "Drawable.h"

typedef struct
{
	Drawable base;
	const SDL_Texture* texture;
	SDL_Rect subRect;
}Sprite;

Sprite*         Sprite_create(const SDL_Rect* destRect, const SDL_Texture* texture, const SDL_Rect* subRect);
void            Sprite_init(Sprite* self, const SDL_Rect* destRect, const SDL_Texture* texture, const SDL_Rect* subRect);

void            Sprite_draw(Drawable* self, SDL_Renderer* renderer);

const SDL_Rect* Sprite_getSubRect(Sprite* self);
void            Sprite_setSubRect(Sprite* self, SDL_Rect* subRect);

void            Sprite_destroy(Sprite* self);

#endif
