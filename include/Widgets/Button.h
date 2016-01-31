#ifndef  BUTTON_INC
#define  BUTTON_INC

#include "Drawable/Sprite.h"
#include "Drawable/Text.h"

typedef struct
{
	Drawable base;
	Sprite* sprite;
	Text*   text;
}Button;

Button* Button_create(void(*callback)(void*), void* data, const SDL_Rect* rect, Sprite* image, Text* text);
void Button_init(Button* self, void(*callback)(void*), void* data, const SDL_Rect* rect, Sprite* image, Text* text);

/** \brief update the Sprite and text position / size. Don't need to be called directly
 * \param self the Button itself*/
void Button_updateDrawableRect(Button* self);
bool Button_howActive(Active* self, const SDL_Event* event);
void Button_draw(Drawable* drawable, Window* window);
void Button_setSize(Drawable* drawable, uint32_t width, uint32_t height);
void Button_setPosition(Drawable* drawable, int32_t x, int32_t y);

/** \brief Set the button's text
 * \param self the Button itself
 * \param text the new Text
 * \param resetRect reset the Button rect or not (if the text is shorter/taller than before and don't have an image, should we reset the Button rect ?)*/
void Button_setText(Button* self, Text* text, bool resetRect);
void Button_destroy(Button* self);

#endif
