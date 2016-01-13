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
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	Drawable_init((Drawable*)self, &rect);

	self->lifes = 3;
	self->animLength = 1;

	self->playerImage = File_create("Resources/player.png");
	if(self->playerImage == NULL)
	{
		perror("Couldn't load the player image file. abort \n");
		return;
	}

	int32_t i;
	for(i=0; i < self->animLength; i++)
	{
		self->staticAnimation = (StaticAnimation**)malloc(sizeof(StaticAnimation*)*self->animLength);
		self->staticAnimation[0] = StaticAnimation_create(NULL, self->playerImage->texture, 0, i*32, 2, 0, 29, 32, 3, 3, 0, 8);
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

}

void Player_draw(Drawable* drawable, Window* window)
{
	Player* self = (Player*)drawable;
	((Drawable*)(self->staticAnimation[self->idAnimation]))->draw((Drawable*)(self->staticAnimation[self->idAnimation]), window);
}

bool Player_howActive(Active* active, SDL_Event* e)
{
	Player* self = (Player*)active;
	if(e->type == SDL_KEYDOWN)
	{
		//si flêche, change orientation, return true;
	}
	return false;
}

void Player_activeIt(Active* active)
{
	Player* self = (Player*)active;
	const SDL_Rect* rect = Drawable_getRect((Drawable*)(self));

	switch(self->orientation)
	{
		case TOP:
			((Drawable*)(self))->setPosition((Drawable*)(self), rect->x, rect->y - 10);
			break;
		case BOTTOM:
			break;
		case LEFT:
			break;
		case RIGHT:
			break;
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
