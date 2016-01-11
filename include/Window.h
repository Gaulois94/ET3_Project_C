#ifndef  WINDOW_INC
#define  WINDOW_INC

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define FPS 60

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "typedefine.h"

typedef struct
{
	SDL_Window*   window;
	SDL_Renderer* renderer;
	uint64_t timer;
}Window;

Window* Window_init(uint32_t width, uint32_t height, const char* title);
void    Window_destroy(Window* window);

bool    Window_initSDL();
bool    Window_finishSDL();
void    Window_fpsManager(Window* window);

void    Window_clear(Window* window);
void    Window_display(Window* window);


#endif
