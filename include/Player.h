#ifndef  PLAYER_INC
#define  PLAYER_INC

#include "stdint.h"
#include "Drawable/StaticAnimation.h"
#include "File.h"

#define PLAYER_SPEED_X 800
#define PLAYER_SPEED_Y 100

typedef enum{RIGHT, LEFT, TOP, BOTTOM} Orientation;

typedef struct
{
	Drawable base;
	File* playerImage;
	StaticAnimation** staticAnimation;
	uint8_t    animLength;
	uint8_t    idAnimation;
	uint8_t    lifes;
	Orientation orientation;
}Player;

Player* Player_create(int32_t x, int32_t y);
void    Player_init(Player* player, int32_t x, int32_t y);
bool    Player_howActive(Active* active, SDL_Event* e);
void    Player_activeIt(Active* active);
void    Player_draw(Drawable* drawable, Window* window);
void    Player_setPosition(Drawable* drawable, int32_t x, int32_t y);
void    Player_setStatic(Drawable* drawable, bool isStatic);
void    Player_setSize(Drawable* drawable, uint32_t width, uint32_t height);
void    Player_destroy(Drawable* drawable);

#endif
