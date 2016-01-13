#include "File.h"

File* File_create(const char* path)
{
	File* file = (File*)malloc(sizeof(File));
	SDL_Surface* image;
	SDL_Texture* texture=NULL;
	if((image = IMG_Load(path)) != NULL)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(globalVar_window->renderer, image);
		file->texture = texture;
		SDL_FreeSurface(image);

		File* file = (File*)malloc(sizeof(File));
		file->texture = texture;
		return file;
	}
	return NULL;
}

void File_destroy(File* self)
{
	SDL_DestroyTexture(self->texture);
	free(self);
}
