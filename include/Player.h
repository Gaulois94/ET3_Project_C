#ifndef  PLAYER_INC
#define  PLAYER_INC

#include "stdint.h"
#include "Animation.h"

#define PLAYER_SPEED_X 800
#define PLAYER_SPEED_Y 100

typedef struct
{
	Element    base;
	uint8_t    lifes;
}Player;

#endif
