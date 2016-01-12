#ifndef  DRAWABLE_INC
#define  DRAWABLE_INC

#include "SDL2/SDL.h"
#include "Widgets/Active.h"
#include "typedefine.h"
#include "Window.h"

/* \struct Drawable
 * \brief Drawing things on the screen. Don't use this structure directly : use another which inherit from it.*/
typedef struct Drawable
{
	Active base;
	SDL_Rect rect; /*!< Destination rect.*/
	void(*draw)(struct Drawable*, Window*); /* !<Function which point to the correct draw function (use for inheritance) */
	void(*destroy)(struct Drawable*);
	void(*setStatic)(struct Drawable*, bool);
	void(*setPosition)(struct Drawable*, int32_t, int32_t);
	void(*setSize)(struct Drawable*, uint32_t width, uint32_t height);
	bool isStatic;
}Drawable;

void Drawable_init(Drawable* self, const SDL_Rect* destRect);
void Drawable_draw(Drawable* self, Window* window); //This function does nothing, but is necessary for the pointer Drawable::draw. We keep the Window as a parameter, even if globalVar_window exist, for the modularity of the code. Indeed, the class Drawable and others class like this one could be reused in other projects.
const SDL_Rect* Drawable_getRect(const Drawable* self);
void Drawable_setRect(Drawable* self, const SDL_Rect* rect);
SDL_Rect Drawable_getRectOnScreen(const Drawable* self, const Window* window);
bool Drawable_pointOnRect(const Drawable* drawable, const SDL_Point* p);
bool Drawable_pointOnRectOnScreen(const Drawable* self, const Window* window, const SDL_Point* p);
void Drawable_setSize(Drawable* self, uint32_t width, uint32_t height);
void Drawable_setPosition(Drawable* self, int32_t x, int32_t y);
void Drawable_setStatic(Drawable* self, bool isStatic);

void copyRect(SDL_Rect* dest, const SDL_Rect* src);
const SDL_Rect* evaluateRect(const SDL_Rect* rect);

void Drawable_destroy(Drawable* self);
bool pointOnRect(const SDL_Rect* rect, const SDL_Point* p);

#endif
