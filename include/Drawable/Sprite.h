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

/* \brief create and initialize a structure Sprite
   \param destRect
   \param texture
   \param subRect
   \return the structure Sprite
*/
Sprite*         Sprite_create(const SDL_Rect* destRect, SDL_Texture* texture, const SDL_Rect* subRect);

/* \brief initialize a structure Sprite
   \param self the structure Sprite
   \param destRect 
   \param texture
   \param subRect
*/
void            Sprite_init(Sprite* self, const SDL_Rect* destRect, SDL_Texture* texture, const SDL_Rect* subRect);

void            Sprite_draw(Drawable* self, Window* window);

/* \brief change the rectangle subRcet of the texture bound to the sprite
   \param self the structure Sprite
   \return the subRect
*/
const SDL_Rect* Sprite_getSubRect(const Sprite* self);

/* \brief change the rectangle subRcet of the texture bound to the sprite
   \param self the structure Sprite
   \param subRect the new subRect
*/
void            Sprite_setSubRect(Sprite* self, const SDL_Rect* subRect);

#endif
