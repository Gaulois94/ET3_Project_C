#include "Window.h"

Window* Window_init(uint32_t width, uint32_t height, const char* title)
{
	Window* window = (Window*)malloc(sizeof(Window));
	window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(window->window == NULL)
	{
		printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
		free(window);
		return NULL;
	}
	window->renderer = SDL_CreateRenderer(window->window, 0, SDL_RENDERER_TARGETTEXTURE);
	if(window->renderer == NULL)
	{
		printf("Couldn't create the window window. SDL_ERROR :  %s\n", SDL_GetError());
		free(window->window);
		free(window);
		return NULL;
	}

	window->timer = 0;
	window->cameraX = window->cameraY = 0;
	window->framerate = FPS;

	return window;
}

void Window_clear(Window* window)
{
	SDL_RenderClear(window->renderer);
}

void Window_display(Window* window)
{
	SDL_RenderPresent(window->renderer);
	Window_fpsManager(window);
}

SDL_Point Window_convertToScreenCoord(const Window* window, const SDL_Point* point)
{
	SDL_Point p = *point;
	p.x -= window->cameraX;
	p.y -= window->cameraY;
	return p;
}

void Window_fpsManager(Window* window)
{
	//Avoid overflow
	if(SDL_GetTicks() < window->timer)
		window->timer = SDL_GetTicks();

	//Then Delay
	SDL_Delay(fmax(0, (float)(1.0/FPS) * 1000 - (SDL_GetTicks() - window->timer)));
	window->framerate = 1/((SDL_GetTicks() - window->timer));
	window->timer = SDL_GetTicks();
}

bool Window_initSDL()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
		return 0;
	}

	if(TTF_Init() == -1)
    {
        return 0;    
    }

	//Init the music
	if(SDL_Init(SDL_INIT_AUDIO)==-1) 
	{
		printf("SDL_Init: %s\n", SDL_GetError());
		return 0;
	}

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1 )
    {
        return 0;    
    }

	return 1;
}


void Window_moveCamera(Window* window, uint32_t x, uint32_t y)
{
	Window_setCameraCoords(window, window->cameraX+x, window->cameraY+y);
}

void Window_setCameraCoords(Window* window, uint32_t x, uint32_t y)
{	
	window->cameraX = x;
	window->cameraY = y;	
}

void Window_destroy(Window* window)
{
	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->window);
	free(window);
}

void Window_finishSDL()
{
	TTF_Quit();
	SDL_Quit();
}
