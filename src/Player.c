#include "Player.h"

Player* Player_create(int32_t x, int32_t y)
{
	Player* self = (Player*)malloc(sizeof(Player));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}
	Player_init(self, x, y);
}

void Player_init(Player* self, int32_t x, int32_t y)
{
	self->stillDown = false;
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = ANIME_SIZE_X;
	rect.h = ANIME_SIZE_Y;
	Drawable_init((Drawable*)self, &rect);

	self->lifes = 3;
	self->animLength = 4;

	self->playerImage = File_create("Resources/player.png");
	if(self->playerImage == NULL)
	{
		perror("Couldn't load the player image file. abort \n");
		return;
	}

	int32_t i;
	self->staticAnimation = (StaticAnimation**)malloc(sizeof(StaticAnimation*)*self->animLength);
	for(i=0; i < self->animLength; i++)
	{
		self->staticAnimation[i] = StaticAnimation_create(NULL, self->playerImage->texture, 3*i*ANIME_SIZE_X, 0, 0, 0, ANIME_SIZE_X, ANIME_SIZE_Y, 3, 3, 0, 8);
		Animation_setInAnimation((Animation*)(self->staticAnimation[i]), false, true);
	}

	self->idAnimation = 0;
	self->orientation=RIGHT;
	Player_setPosition((Drawable*)self, x, y);

	Drawable* selfDrawable = (Drawable*)self;
	selfDrawable->draw        = &Player_draw;
	selfDrawable->setPosition = &Player_setPosition;
	selfDrawable->setSize     = &Player_setSize;
	selfDrawable->setStatic   = &Player_setStatic;
	selfDrawable->destroy     = &Player_destroy;

	Active* selfActive = (Active*)self;
	selfActive->autoDisactive = true;
	selfActive->howActive = &Player_howActive;
	selfActive->activeIt = &Player_activeIt;
	selfActive->update   = &Player_update;
}

void Player_draw(Drawable* drawable, Window* window)
{
	Player* self = (Player*)drawable;
	((Drawable*)(self->staticAnimation[self->idAnimation]))->draw((Drawable*)(self->staticAnimation[self->idAnimation]), window);
}

void Player_update(Active* active, Window* window)
{
	Player* self = (Player*)active;
	if(!self->stillDown)
		return;

	const SDL_Rect* rect = Drawable_getRect((Drawable*)(self));
	int32_t xScroll=0, yScroll=0;
	switch(self->orientation)
	{
		case TOP:
			((Drawable*)(self))->setPosition((Drawable*)(self), rect->x, rect->y - 5);
			yScroll = -5;
			break;
		case BOTTOM:
			((Drawable*)(self))->setPosition((Drawable*)(self), rect->x, rect->y + 5);
			yScroll = 5;
			break;
		case LEFT:
			((Drawable*)(self))->setPosition((Drawable*)(self), rect->x - 5, rect->y);
			xScroll = -5;
			break;
		case RIGHT:
			((Drawable*)(self))->setPosition((Drawable*)(self), rect->x + 5, rect->y);
			xScroll = 5;
			break;
	}
	Window_moveCamera(window, xScroll, yScroll);
}

bool Player_howActive(Active* active, const SDL_Event* e)
{
	Player* self = (Player*)active;
	if(e->type == SDL_KEYDOWN)
	{
		if(e->key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			self->orientation = LEFT;
			self->idAnimation = LEFT;
		}

		else if(e->key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			self->orientation = RIGHT;
			self->idAnimation = RIGHT;
		}

		else if(e->key.keysym.scancode == SDL_SCANCODE_UP)
		{
			self->orientation = TOP;
			self->idAnimation = TOP;
		}

		else if(e->key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
			self->orientation = BOTTOM;
			self->idAnimation = BOTTOM;
		}
		else
			return false;
		return true;
	}

	if(e->type == SDL_KEYUP)
		if(e->key.keysym.scancode == SDL_SCANCODE_LEFT && self->orientation == LEFT || e->key.keysym.scancode == SDL_SCANCODE_RIGHT && self->orientation == RIGHT || e->key.keysym.scancode == SDL_SCANCODE_DOWN && self->orientation == BOTTOM || e->key.keysym.scancode == SDL_SCANCODE_UP && self->orientation == TOP)
			return true;
	return false;
}

void Player_activeIt(Active* active, const SDL_Event* e)
{
	Player* self = (Player*)active;
	uint32_t i;
	if(e->type == SDL_KEYDOWN)
	{
		if(self->stillDown)
			return;
		for(i=0; i < self->animLength; i++)
			Animation_setInAnimation((Animation*)(self->staticAnimation[i]), true, true);
		self->stillDown = true;
	}

	else if(e->type == SDL_KEYUP)
	{
		printf("up \n");
		self->stillDown = false;
		for(i=0; i < self->animLength; i++)
			Animation_setInAnimation((Animation*)(self->staticAnimation[i]), false, true);
	}
}

void Player_setPosition(Drawable* drawable, int32_t x, int32_t y)
{
	Player* self = (Player*)drawable;
	int32_t i;
	for(i=0; i < self->animLength; i++)
		((Drawable*)(self->staticAnimation[i]))->setPosition((Drawable*)(self->staticAnimation[i]), x, y);
	Drawable_setPosition(drawable, x, y);
}

void Player_setSize(Drawable* drawable, uint32_t width, uint32_t height)
{
	Player* self = (Player*)drawable;
	int32_t i;
	for(i=0; i < self->animLength; i++)
		((Drawable*)(self->staticAnimation[i]))->setSize((Drawable*)(self->staticAnimation[i]), width, height);
	Drawable_setSize(drawable, width, height);
}

void Player_setStatic(Drawable* drawable, bool isStatic)
{
	Player* self = (Player*)drawable;
	int32_t i;
	for(i=0; i < self->animLength; i++)
		((Drawable*)(self->staticAnimation[i]))->setStatic((Drawable*)(self->staticAnimation[i]), isStatic);
	Drawable_setStatic(drawable, isStatic);
}

void Player_destroy(Drawable* drawable)
{
	Player* self = (Player*)drawable;
	int8_t i;
	for(i=0; i < self->animLength; i++)
		if(self->staticAnimation[i])
			((Drawable*)(self->staticAnimation[i]))->destroy((Drawable*)(self->staticAnimation[i]));
	File_destroy(self->playerImage);
	free(self->staticAnimation);
	Drawable_destroy(drawable);
}
