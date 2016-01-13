#ifndef  PLAYER_INC
#define  PLAYER_INC

#include "stdint.h"
#include "Drawable/StaticAnimation.h"

#define PLAYER_SPEED_X 800
#define PLAYER_SPEED_Y 100

typedef enum{TOP, BOTTOM, LEFT, RIGHT} Orientation;

typedef struct
{
	Drawable base;
	StaticAnimation* staticAnimation;
	uint8_t    lifes;
	Orientation orientation;
}Player;

Player* Player_create(int32_t x, int32_t y);
void    Player_init(Player* player, int32_t x, int32_t y);
bool    Player_howActive(Active* active, SDL_Event* e);
void    Player_activeIt(Active* active);
void    Player_destroy(Player* player);

#endif
