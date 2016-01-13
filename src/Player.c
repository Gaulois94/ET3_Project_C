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
	self->staticAnimation = NULL;
	self->orientation=RIGHT;
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

void Player_destroy(Player* player)
{
	free(player);
}
