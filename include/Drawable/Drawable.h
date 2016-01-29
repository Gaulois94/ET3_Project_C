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

/* \brief initialize a structure Drawable
   \param self the structure Drawable
   \param destRect the rectangle used in the structure
*/
void Drawable_init(Drawable* self, const SDL_Rect* destRect);

void Drawable_draw(Drawable* self, Window* window); //This function does nothing, but is necessary for the pointer Drawable::draw. We keep the Window as a parameter, even if globalVar_window exist, for the modularity of the code. Indeed, the class Drawable and others class like this one could be reused in other projects.

/* \brief return the rectangle of a structure Drawable
   \param self the structure Drawable
   \return the rectangle
*/
const SDL_Rect* Drawable_getRect(const Drawable* self);

/* \brief change the rectangle of a structure Drawable
   \param self the structure Drawable
   \param rect the new rectangle
*/
void Drawable_setRect(Drawable* self, const SDL_Rect* rect);

/* \brief return a rectangle on the screen for a structure Drawable
   \param self the structure Drawable
   \param window the window in which we want the screen
   \return the rectangle
*/
SDL_Rect Drawable_getRectOnScreen(const Drawable* self, const Window* window);

/* \brief check if a point is on a rect of a structure Drawable
   \param self the structure Drawable
   \param p the point
   \return a boolean that indicate if the point is on the rectangle or not
*/
bool Drawable_pointOnRect(const Drawable* drawable, const SDL_Point* p);

/* \brief check if a point is on a rect that is on the screen
   \param self a structure Drawable
   \param window a window
   \param p the point
   \return a boolean that indicate if the point is on the rectangle or not
*/
bool Drawable_pointOnRectOnScreen(const Drawable* self, const Window* window, const SDL_Point* p);

/* \brief change the size of the rectangle of a structure Drawable
   \param self the structure Drawable
   \param width the width
   \param height the height
*/
void Drawable_setSize(Drawable* self, uint32_t width, uint32_t height);

/* \brief change the position of the rectangle of a structure Drawable
   \param x
   \param y
*/
void Drawable_setPosition(Drawable* self, int32_t x, int32_t y);

/* \brief change the boolean isStatic of a structure Drawable
   \param self the structure Drawable
   \param isStatic the new boolean
*/
void Drawable_setStatic(Drawable* self, bool isStatic);

void Drawable_move(Drawable* self, int32_t x, int32_t y);


/* \brief copy a rectangle
   \param dest rectangle of destination
   \param src rectangle source
*/
void copyRect(SDL_Rect* dest, const SDL_Rect* src);

/* \brief check if the rectangle exist
   \param rect the rectangle
   \return the rectangle
*/
const SDL_Rect* evaluateRect(const SDL_Rect* rect);

/* \brief destroy a structure Drawable
   \param self the tructure Drawable
*/
void Drawable_destroy(Drawable* self);

/* \brief check if a point is on a rect
   \param rect the rectangle
   \param p the point
   \return a boolean that indicate if the point is on the rectangle or not
*/
bool pointOnRect(const SDL_Rect* rect, const SDL_Point* p);

#endif
