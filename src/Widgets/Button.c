#include "Widgets/Button.h"

Button* Button_create(void(*callback)(void*), void* data, const SDL_Rect* rect, Sprite* image, Text* text)
{
	Button* button = (Button*)malloc(sizeof(Button));
	if(button == NULL)
	{
		perror("Error on malloc");
		return NULL;
	}
	Button_init(button, callback, data, rect, image, text);
	return button;
}

void Button_init(Button* self, void(*callback)(void*), void* data, const SDL_Rect* rect, Sprite* image, Text* text)
{
	Drawable_init((Drawable*)self, rect);
	((Drawable*)self)->setPosition = &Button_setPosition;
	((Drawable*)self)->setSize = &Button_setSize;
	((Drawable*)self)->draw = &Button_draw;
	((Active*)self)->howActive = &Button_howActive;
	((Active*)self)->autoDisactive = true;
	self->sprite = image;
	self->text = text;
	rect = Drawable_getRect((Drawable*)self);

	if(rect->w == 0 && rect->h == 0)
	{
		if(self->sprite)
		{
			const SDL_Rect* rs = Drawable_getRect((Drawable*)self->sprite);
			((Drawable*)self)->setSize((Drawable*)self, rs->w, rs->h);
		}
		else if(self->text)
		{
			const SDL_Rect* rt = Drawable_getRect((Drawable*)self->text);
			((Drawable*)self)->setSize((Drawable*)self, rt->w, rt->h);
		}
	}

	Button_updateDrawableRect(self);
}

bool Button_howActive(Active* self, const SDL_Event* event)
{
	if(event->type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_Point p;
		p.x = event->button.x;
		p.y = event->button.y;
		if(Drawable_pointOnRect((Drawable*)self, &p))
			return true;
	}
	return false;
}

void Button_updateDrawableRect(Button* self)
{
	const SDL_Rect* rect = Drawable_getRect((Drawable*)self);
	if(self->sprite)
		Drawable_setRect(((Drawable*)self->sprite), rect);

	if(self->text)
	{
		const SDL_Rect* textRect = Drawable_getRect((Drawable*)self->text);
		float scale = fmin(rect->w / (float)textRect->w, rect->h / (float)textRect->h);
		Drawable_setSize(((Drawable*)self->text), textRect->w * scale, textRect->h * scale);

		int32_t buttonCenterX = rect->x + rect->w / 2;
		int32_t buttonCenterY = rect->y + rect->h / 2;

		textRect = Drawable_getRect((Drawable*)self->text);
		Drawable_setPosition((Drawable*)self->text, buttonCenterX-textRect->w/2, buttonCenterY-textRect->h/2);
	}
}

void Button_setPosition(Drawable* drawable, int32_t x, int32_t y)
{
	Drawable_setPosition(drawable, x, y);
	Button_updateDrawableRect((Button*)drawable);
}

void Button_setSize(Drawable* drawable, uint32_t w, uint32_t h)
{
	Drawable_setSize(drawable, w, h);
	Button_updateDrawableRect((Button*)drawable);
}

void Button_setText(Button* self, Text* text, bool resetRect)
{
	self->text = text;
	if(resetRect)
	{
		if(self->sprite)
		{
			const SDL_Rect* rs = Drawable_getRect((Drawable*)self->sprite);
			((Drawable*)self)->setSize((Drawable*)self, rs->w, rs->h);
		}
		else if(self->text)
		{
			const SDL_Rect* rt = Drawable_getRect((Drawable*)self->text);
			((Drawable*)self)->setSize((Drawable*)self, rt->w, rt->h);
		}
	}
	Button_updateDrawableRect(self);
}

void Button_draw(Drawable* drawable, Window* window)
{
	Button* self = (Button*)drawable;
	if(self->sprite)
		Sprite_draw(((Drawable*)self->sprite), window);
	if(self->text)
		Text_draw(((Drawable*)self->text), window);
}

void Button_destroy(Button* self)
{
	Drawable_destroy((Drawable*)self);
}
