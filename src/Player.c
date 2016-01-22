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

	self->lifes      = 3;
	self->animLength = 4;
	self->speedY     = 0;
	self->jump       = true;

	self->playerImage = File_create("Resources/Mario.png");
	if(self->playerImage == NULL)
	{
		perror("Couldn't load the player image file. abort \n");
		return;
	}

	//Load animation;
	self->staticAnimation = (StaticAnimation**)malloc(sizeof(StaticAnimation*)*self->animLength);
	self->staticAnimation[LEFT]  = StaticAnimation_create(NULL, self->playerImage->texture, 0, 0, 1, 1, ANIME_SIZE_X, ANIME_SIZE_Y, 2, 2, 0, 8);
	self->staticAnimation[RIGHT] = StaticAnimation_create(NULL, self->playerImage->texture, 0, ANIME_SIZE_Y+1, 1, 1, ANIME_SIZE_X, ANIME_SIZE_Y, 2, 2, 0, 8);
	self->staticAnimation[JUMPL] = StaticAnimation_create(NULL, self->playerImage->texture, 2*(ANIME_SIZE_X+2), 0, 1, 1, ANIME_SIZE_X, ANIME_SIZE_Y, 1, 1, 0, 8);
	self->staticAnimation[JUMPR] = StaticAnimation_create(NULL, self->playerImage->texture, 2*(ANIME_SIZE_X+2), ANIME_SIZE_Y+1, 1, 1, ANIME_SIZE_X, ANIME_SIZE_Y, 1, 1, 0, 8);

	uint32_t i;
	for(i=0; i < self->animLength; i++)
		Animation_setInAnimation((Animation*)(self->staticAnimation[i]), false, true);

	self->idAnimation = 0;
	self->action=RIGHT;
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

	self->jumpScancode  = self->jumpScancode;
	self->leftScancode  = self->rightScancode;
	self->rightScancode = self->leftScancode;
}

void Player_stop(Player* self)
{
	self->stillDown = false;
	self->speedY    = 0;
	self->jump      = false;
}

void Player_draw(Drawable* drawable, Window* window)
{
	Player* self = (Player*)drawable;
	((Drawable*)(self->staticAnimation[self->idAnimation]))->draw((Drawable*)(self->staticAnimation[self->idAnimation]), window);
}

void Player_update(Active* active)
{
	return;
}

void Player_updateGravity(Player* self)
{
	Player_move(self, 0, self->speedY);
	if(self->jump && self->speedY != 0 && self->action == LEFT)
		self->idAnimation = JUMPL;

	else if(self->jump && self->speedY != 0 && self->action == RIGHT)
		self->idAnimation = JUMPR;

	else if(self->speedY == 0)
	{
		if(self->action == LEFT)
			self->idAnimation = LEFT;
		else
			self->idAnimation = RIGHT;
	}
}

void Player_updateMovement(Player* self)
{
	if(!self->stillDown)
		return;

	if(self->action == LEFT)
	{
		if(!self->jump)
			self->idAnimation = LEFT;
		Player_move(self, -2, 0);
	}
	else if(self->action == RIGHT)
	{
		if(!self->jump)
			self->idAnimation = RIGHT;
		Player_move(self, 2, 0);
	}
}

void Player_move(Player* self, int32_t x, int32_t y)
{
	const SDL_Rect* rect = Drawable_getRect((Drawable*)(self));
	((Drawable*)(self))->setPosition((Drawable*)(self), rect->x + x, rect->y + y);
}

bool Player_howActive(Active* active, const SDL_Event* e)
{
	Player* self = (Player*)active;
	if(e->type == SDL_KEYDOWN)
	{
		if(e->key.keysym.scancode == self->leftScancode)
			self->action = LEFT;

		else if(e->key.keysym.scancode == self->rightScancode)
			self->action = RIGHT;

		else if(e->key.keysym.scancode == self->jumpScancode)
			self->jump = true;
		else
			return false;
		return true;
	}

	if(e->type == SDL_KEYUP)
		if(e->key.keysym.scancode == self->leftScancode && self->action == LEFT || e->key.keysym.scancode == self->rightScancode && self->action == RIGHT)
			return true;
	return false;
}

void Player_activeIt(Active* active, const SDL_Event* e)
{
	Player* self = (Player*)active;
	uint32_t i;
	if(e->type == SDL_KEYDOWN)
	{
		//If the key is jump
		if(e->key.keysym.scancode == self->jumpScancode)
		{
			//and that we are already jumping
			if(self->speedY != 0)
				return;
			else
				self->speedY = JUMP_SPEED;
			return;
		}

		if(self->stillDown)
			return;

		uint32_t i;
		for(i=0; i < self->animLength; i++)
			Animation_setInAnimation((Animation*)(self->staticAnimation[i]), true, true);
		self->stillDown = true;
	}

	else if(e->type == SDL_KEYUP)
	{
		if(e->key.keysym.scancode == self->jumpScancode)
			return;
		self->stillDown = false;
		uint32_t i;
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

void Player_setScancode(Player* self, uint32_t jump, uint32_t left, uint32_t right)
{
	self->leftScancode  = left;
	self->rightScancode = right;
	self->jumpScancode  = jump;
}

float Player_getSpeedY(const Player* player)
{
	return player->speedY;
}

void Player_setSpeedY(Player* self, float speed)
{
	if(speed > MAX_SPEED_GRAVITY)
		speed = MAX_SPEED_GRAVITY;
	self->speedY = speed;
	if(speed == 0)
		self->jump = false;
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
