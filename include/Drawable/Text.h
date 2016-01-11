#ifndef  TEXT_INC
#define  TEXT_INC

#include "Drawable/Drawable.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "ResourcesManager.h"
#include "globalVar.h"

/* \struct Text
 * \brief structure for drawing and handling texts */
typedef struct Text
{
	Drawable base;
	SDL_Texture* texture;
	SDL_Color*   color;
	TTF_Font*    font;
	char*  text;
}Text;

Text* Text_create(const SDL_Rect* destRect, SDL_Renderer* renderer, SDL_Color* color, TTF_Font*font, const char* text);
bool  Text_init(Text* self, const SDL_Rect* destRect, SDL_Renderer* renderer, SDL_Color* color, TTF_Font* font, const char* text);
void  Text_draw(Drawable* self, SDL_Renderer* renderer);
bool  Text_setText(Text* self, SDL_Renderer* renderer, const char* text);
void  Text_destroy(Drawable* self);

#endif
