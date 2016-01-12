#include "Drawable/Text.h"

Text* Text_create(const SDL_Rect* destRect, Window* window, SDL_Color* color, TTF_Font*font, const char* text)
{
	Text* self = (Text*)malloc(sizeof(Text));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}

	if(Text_init(self, destRect, window, color, font, text) == -1)
	{
		free(self);
		return NULL;
	}

	return self;
}

bool Text_init(Text* self, const SDL_Rect* destRect, Window* window, SDL_Color* color, TTF_Font* font, const char* text)
{
	Drawable_init((Drawable*)self, destRect);
	((Drawable*)self)->destroy = &Text_destroy;
	self->color = color;
	self->font  = font;
	self->autoSize = true;

	self->base.draw = &Text_draw;	
	char* t     = (char*)malloc(sizeof(char)*(1+strlen(text)));
	strcpy(t, text);
	self->text  = t;

	return Text_setText(self, window, text);
}

void Text_draw(Drawable* self, Window* window)
{
	Text* text = (Text*)self;
	SDL_Rect rect = Drawable_getRectOnScreen((Drawable*)text, window);
	SDL_RenderCopy(window->renderer, text->texture, NULL, &rect);
}

void Text_setAutoSize(Text* self, bool autoSize, bool reset)
{
	self->autoSize = autoSize;
	if(reset && self->texture)
	{
		int32_t w, h;
		SDL_QueryTexture(self->texture, NULL, NULL, &w, &h)
		Drawable_setSize((Drawable*)self, w, h);
	}
}

bool Text_setText(Text* self, Window* window, const char* text)
{
	SDL_Surface *textSurface;
	if(!(textSurface = TTF_RenderText_Solid(self->font, text, *(self->color))))
	{
		printf("Couldn't create the text %s.\n", text);
		return -1;
	}

	if(self->texture != NULL)
		free(self->texture);

	self->texture = SDL_CreateTextureFromSurface(window->renderer, textSurface);
	if(self->autoSize)
	{
		uint32_t w, h;
		SDL_QueryTexture(self->texture, NULL, NULL, &w, &h);
		Drawable_setSize((Drawable*)self, w, h);
	}
	free(textSurface);
	return 0;
}

void Text_destroy(Drawable* self)
{
	Text* text = (Text*)self;
	if(text == NULL)
		return;

	if(text->text)
		free(text->text);
	if(text->texture)
		free(text->texture);
	Drawable_destroy((Drawable*)text);
}
