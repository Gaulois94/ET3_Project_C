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

Player* Player_create();
void    Player_init(Player* player);
void    Player_destroy(Player* player);

#endif
