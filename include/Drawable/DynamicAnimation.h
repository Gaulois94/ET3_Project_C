#ifndef  DYNAMICANIMATION_INC
#define  DYNAMICANIMATION_INC

#include "Drawable/Animation.h"

typedef struct
{
	Animation base;
	SDL_Rect* rect;
}DynamicAnimation;

/* \brief create and initialize a structure DynamicAnimation
   \param dest use to initialize the animation
   \param texture use to initialize the animation
   \param rectAnimation
   \param maxN use to initialize the animation
   \param currentN use to initialize the animation
   \param nbFrame use to initialize the animation
   \return 
*/
DynamicAnimation* DynamicAnimation_create(const SDL_Rect* dest, SDL_Texture* texture, const SDL_Rect** rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame);

/* \brief initialize a structrure DynamicAnimation
   \param self the structure DynamicAnimation
   \param dest use to initialize the animation
   \param texture use to initialize the animation
   \param rectAnimation
   \param maxN use to initialize the animation
   \param currentN use to initialize the animation
   \param nbFrame use to initialize the animation
*/
void DynamicAnimation_init(DynamicAnimation* self, const SDL_Rect* dest, SDL_Texture* texture, const SDL_Rect** rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame);
void DynamicAnimation_setSubNSpriteRect(Animation* self, uint32_t n);
void DynamicAnimation_destroy(Drawable* self);

#endif
