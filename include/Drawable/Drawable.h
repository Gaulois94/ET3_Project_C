#ifndef  DRAWABLE_INC
#define  DRAWABLE_INC

#include "SDL2/SDL.h"

/* \struct Drawable
 * \brief Drawing things on the screen. Don't use this structure directly : use another which inherit from it.*/
typedef struct Drawable
{
	SDL_Rect rect; /*!< Destination rect.*/
	void(*draw)(struct Drawable*, SDL_Renderer*); /* !<Function which point to the correct draw function (use for inheritance) */
}Drawable;

void Drawable_init(Drawable* self, const SDL_Rect* destRect);
void Drawable_draw(Drawable* self, SDL_Renderer* renderer); //This function does nothing, but is necessary for the pointer Drawable::draw. We keep the SDL_Renderer as a parameter, even if globalVar_window exist, for the modularity of the code. Indeed, the class Drawable and others class like this one could be reused in other projects.
const SDL_Rect* Drawable_getRect(Drawable* self);
void Drawable_setSize(Drawable* self, uint32_t width, uint32_t height);
void Drawable_setPosition(Drawable* self, int32_t x, int32_t y);

void copyRect(SDL_Rect* dest, const SDL_Rect* src);
const SDL_Rect* evaluateRect(const SDL_Rect* rect);

#endif
