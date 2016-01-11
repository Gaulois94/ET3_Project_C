#ifndef  PLAYER_INC
#define  PLAYER_INC

#include "stdint.h"
#include "Drawable/StaticAnimation.h"

#define PLAYER_SPEED_X 800
#define PLAYER_SPEED_Y 100

typedef struct
{
	StaticAnimation base;
	uint8_t    lifes;
}Player;

Player* Player_create();
void    Player_destroy(Player* player);

#endif
