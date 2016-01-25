#ifndef  GOOMBA_INC
#define  GOOMBA_INC

#include "Ennemies/Ennemy.h"
#include "Drawable/DynamicAnimation.h"

typedef struct
{
	Ennemy base;
}Goomba;

Tile* Goomba_create(const SDL_Rect* dest, SDL_Texture* texture, SDL_Rect* rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame);
void  Goomba_init(Goomba* self, const SDL_Rect* dest, SDL_Texture* texture, SDL_Rect* rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame);

#endif
