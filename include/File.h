#ifndef  FILE_INC
#define  FILE_INC

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

typedef struct
{
	SDL_Texture* texture;
}File;

File* File_create(const char* path);
SDL_Texture* File_getTexture(File* self);
void  File_destroy(File* self);

#endif
