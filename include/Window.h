#ifndef  WINDOW_INC
#define  WINDOW_INC

#include "SDL2/SDL.h"

typedef struct
{
	SDL_Window*   window;
	SDL_Renderer* renderer;
	uint64_t timer;
}Window;

SDL_Window* Window_init(uint32_t width, uint32_t height, const char* title);
void        Window_destroy(SDL_Window* window);

int  Window_initVideo(Window* window);
void fpsManager(Window* window);

void Window_clear(SDL_Window* window);
void Window_display(SDL_Window* window);


#endif
