#include "Player.h"

Player* Player_create()
{
	return NULL;
}

void Player_init(Player* player)
{

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
