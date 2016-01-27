#ifndef  WINDOW_INC
#define  WINDOW_INC

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define FPS 60

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "typedefine.h"

typedef struct
{
	SDL_Window*   window;
	SDL_Renderer* renderer;

	uint64_t timer;
	int32_t cameraX;
	int32_t cameraY;
	int64_t framerate;
}Window;

Window*      Window_init(uint32_t width, uint32_t height, const char* title);
void         Window_destroy(Window* window);

bool         Window_initSDL();
void         Window_finishSDL();
void         Window_fpsManager(Window* window);

SDL_Point    Window_convertToScreenCoord(const Window* window, const SDL_Point* point);

void         Window_moveCamera(Window* window, uint32_t x, uint32_t y);
void         Window_setCameraCoords(Window* window, uint32_t x, uint32_t y);

void         Window_clear(Window* window);
void         Window_display(Window* window);

#endif
