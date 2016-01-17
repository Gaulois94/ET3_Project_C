#ifndef  PLAYER_INC
#define  PLAYER_INC

#include "stdint.h"
#include "Drawable/StaticAnimation.h"
#include "File.h"

#define PLAYER_SPEED_X 800
#define PLAYER_SPEED_Y 100
#define JUMP_SPEED            -7
#define MAX_SPEED_GRAVITY     5
#define ANIME_SIZE_X 16
#define ANIME_SIZE_Y 19

typedef enum{LEFT, JUMPL, RIGHT, JUMPR} Action;

typedef struct
{
	Drawable base;
	File* playerImage;
	StaticAnimation** staticAnimation;
	uint8_t    animLength;
	uint8_t    idAnimation;
	uint8_t    lifes;
	bool stillDown;
	bool jump;
	Action action;
	float      speedY;
}Player;

void    Player_update(Active* active);
void    Player_updateGravity(Player* self);
void    Player_updateMovement(Player* self);
void    Player_move(Player* player, int32_t x, int32_t y);
Player* Player_create(int32_t x, int32_t y);
void    Player_init(Player* player, int32_t x, int32_t y);
bool    Player_howActive(Active* active, const SDL_Event* e);
void    Player_activeIt(Active* active, const SDL_Event* e);
void    Player_draw(Drawable* drawable, Window* window);
void    Player_setPosition(Drawable* drawable, int32_t x, int32_t y);
void    Player_setStatic(Drawable* drawable, bool isStatic);
void    Player_setSize(Drawable* drawable, uint32_t width, uint32_t height);

void    Player_setSpeedY(Player* player, float speed);
float   Player_getSpeedY(const Player* player);
void    Player_destroy(Drawable* drawable);

#endif
