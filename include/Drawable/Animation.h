#ifndef  ANIMATION_INC
#define  ANIMATION_INC

#include "SDL2/SDL.h"
#include "Drawable/Sprite.h"

/** \struct Animation
 * \brief basic abstract class for Animation*/
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

/* \brief initialize a structure Animation
   \param self the structure Animation
   \param destRect use to initialize the sprite
   \param texture use to initialize the sprite
   \param maxN 
   \param currentN
   \param nbFrame
*/
void Animation_init(Animation* self, const SDL_Rect* destRect, SDL_Texture* texture, uint32_t maxN, uint32_t currentN, uint32_t nbFrame);
void Animation_draw(Drawable* self, Window* window);

void Animation_setSubNSpriteRect(Animation* self, uint32_t n);

/* \brief change the boolean inAnimation in a structure Animation
   \param self the structure Animation
   \param inAnimation new inAnimation
   \param reset boolean that indicate if iFrame need to be reset
*/
void Animation_setInAnimation(Animation* self, bool inAnimation, bool reset);


/* \brief return the boolean inAnimation of a structure Animation
   \param self the structure Animation
   \return inAnimation
*/
bool Animation_getInAnimation(const Animation* self);

#endif
