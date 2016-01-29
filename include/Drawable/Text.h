#ifndef  TEXT_INC
#define  TEXT_INC

#include "Drawable/Drawable.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "ResourcesManager.h"

/* \struct Text
 * \brief structure for drawing and handling texts */
typedef struct Text
{
	Drawable base;
	SDL_Texture* texture;
	SDL_Color*   color;
	TTF_Font*    font;
	bool autoSize;
	char*  text;
}Text;

/* \create and initialize a structure Text
   \param destRect rectangle in which the text is written
   \param window windows in which the text is written
   \param color color use to write the text
   \param font font use to write the text
   \param text what we want to write
   \return the structure Text created
*/
Text* Text_create(const SDL_Rect* destRect, Window* window, SDL_Color* color, TTF_Font*font, const char* text);

/* \brief initialize a structure Text
   \param self structure Text
   \param destRect rectangle in which the text is written
   \param window window in which the text is written
   \param color color use to write the text
   \param font font use to write the text
   \param text what we want to write
   \return a boolean that they if we did add the text in the structure
*/
bool  Text_init(Text* self, const SDL_Rect* destRect, Window* window, SDL_Color* color, TTF_Font* font, const char* text);

/* \brief set the boolean to tell at the object Text if it can figure itself its own SDL_Rect
   \param self structure Text
   \param autoSize the new value of autoSize
   \param reset reset the rect at this call of the Text or not.
*/
bool  Text_autoSize(bool autoSize, bool reset);

void  Text_draw(Drawable* self, Window* window);

/* \brief change the text in a structure Text
   \param self structure Text
   \param window window in which the text is written
   \param the new text
   \return a boolean to be sure it's done
*/
bool  Text_setText(Text* self, Window* window, const char* text);
void  Text_destroy(Drawable* self);

#endif
