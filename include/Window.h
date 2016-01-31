#ifndef  WINDOW_INC
#define  WINDOW_INC

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define FPS 60

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
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

/** \brief init the SDL
 * \return tells if the SDL is correcty init or not*/
bool         Window_initSDL();

/** \brief tell if the SDL if finished*/
void         Window_finishSDL();

/** \brief manage the fps of the window. Don't to be used directly
 * \param window the Window itself*/
void         Window_fpsManager(Window* window);

/** \brief convert an absolute position to the window coordinate
 * \param window the Window itself
 * \param point the point to convert
 * \return the SDL_Point to get*/
SDL_Point    Window_convertToScreenCoord(const Window* window, const SDL_Point* point);

/** \brief move the camera
 * \param window the Window itself
 * \param x the x scroll of the Window's camera
 * \param y the y scroll of the Window's camera*/
void         Window_moveCamera(Window* window, uint32_t x, uint32_t y);

/** \brief set the camera position
 * \param window the Window itself
 * \param x the new x position of the camera
 * \param y the new y position of the camera*/
void         Window_setCameraCoords(Window* window, uint32_t x, uint32_t y);

/** \brief clear the window
 * \param window the Window itself*/
void         Window_clear(Window* window);

/** \brief display the contain of the memory card to the Window
 * \param window the Window itself*/
void         Window_display(Window* window);

#endif
