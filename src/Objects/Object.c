#include "Objects/Object.h"

Object* Object_create(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY)
{
	Object* self = (Object*)malloc(sizeof(Object));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	Object_init(self, nbCasesX, nbCasesY, sizeX, sizeY);
	return self;
}

void Object_init(Object* self, uint32_t nbCasesX, uint32_t nbCasesY, uint32_t sizeX, uint32_t sizeY)
{
	Drawable* drawable = (Drawable*)self;
	Drawable_init(drawable, NULL);
	self->sizeX = sizeX;
	self->sizeY = sizeY;
	self->nbCasesX = nbCasesX;
	self->nbCasesY = nbCasesY;
	self->tiles = (Tile***)malloc(nbCasesX * sizeof(Tile**));
	uint32_t i=0;
	uint32_t j;
	for(i=0; i < nbCasesX; i++)
	{
		self->tiles[i] = (Tile**)malloc(nbCasesY * sizeof(Tile*));
		for(j=0; j < nbCasesY; j++)
			self->tiles[i][j] = NULL;
	}

	drawable->setPosition = &Object_setPosition;
	drawable->setSize     = &Object_setSize;
	drawable->setStatic   = &Object_setStatic;
	drawable->draw        = &Object_draw;
	drawable->destroy     = &Object_destroy;

	drawable->setSize(drawable, nbCasesX*sizeX, nbCasesY*sizeY);
	self->info = 0x00;
}

void Object_setStatic(Drawable* self, bool isStatic)
{

}

void Object_draw(Drawable* drawable, Window* window)
{
	Object* self = (Object*)drawable;
	uint32_t i, j;
	for(i=0; i < self->nbCasesX; i++)
		for(j=0; j < self->nbCasesY; j++)
			if(self->tiles[i][j])
				((Drawable*)self->tiles[i][j])->draw((Drawable*)self->tiles[i][j], window);
}

void Object_addTile(Object* self, uint32_t x, uint32_t y, Tile* tile)
{
	if(x >= self->nbCasesX && y >= self->nbCasesY)
		return;
	self->tiles[x][y] = tile;
	Drawable* drawable = (Drawable*)self;
	drawable->setPosition(drawable, drawable->rect.x, drawable->rect.y);
	drawable->setSize(drawable, drawable->rect.w, drawable->rect.h);
}

void Object_setPosition(Drawable* drawable, int32_t x, int32_t y)
{
	Object* self = (Object*)drawable;
	uint32_t i, j;
	const SDL_Rect* rect = Drawable_getRect(drawable);
	float factorX = rect->w / (float)(self->nbCasesX * self->sizeX);
	float factorY = rect->h / (float)(self->nbCasesY * self->sizeY);
	for(i=0; i < self->nbCasesX; i++)
	{
		for(j=0; j < self->nbCasesY; j++)
		{
			if(self->tiles[i][j])
			{
				Drawable* tile = (Drawable*)(self->tiles[i][j]);
				if(tile == NULL)
					continue;
				tile->setPosition(tile, x + factorX * self->sizeX * i, y + factorY * self->sizeY * j);
			}
		}
	}

	Drawable_setPosition(drawable, x, y);
}

void Object_setSize(Drawable* drawable, uint32_t width, uint32_t height)
{
	Object* self = (Object*)drawable;
	Drawable_setSize(drawable, width, height);
	drawable->setPosition(drawable, width, height);

	float factorX = width / (float)(self->nbCasesX * self->sizeX);
	float factorY = height / (float)(self->nbCasesY * self->sizeY);
	uint32_t i, j;
	for(i=0; i < self->nbCasesX; i++)
	{
		for(j=0; j < self->nbCasesY; j++)
		{
			if(self->tiles[i][j])
			{
				Drawable* tile = (Drawable*)(self->tiles[i][j]);
				if(tile == NULL)
					continue;
				tile->setSize(tile, factorX * self->sizeX, factorY * self->sizeY);
			}
		}
	}
}

int32_t Object_getInfo(Object* object)
{
	return object->info;
}

void Object_destroy(Drawable* drawable)
{
	Object* self = (Object*)drawable;
	uint32_t i, j;
	for(i=0; i < self->nbCasesX; i++)
	{
		for(j=0; j < self->nbCasesY; j++)
		{
			Drawable* tile = (Drawable*)(self->tiles[i][j]);
			if(tile != NULL)
				tile->destroy(tile);
		}
		free(self->tiles[i]);
	}
	free(self->tiles);
	free(self);
}
