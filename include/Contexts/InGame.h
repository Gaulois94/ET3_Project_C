#ifndef  INGAME_INC
#define  INGAME_INC

#define GRAVITY 0.3
#define TIMEOUT 400

#include "Contexts/Context.h"
#include "math.h"
#include "Ennemy.h"
#include "Player.h"
#include "Map.h"
#include "Drawable/Text.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct
{
	Context  base;

	Ennemy** ennemies;
	uint32_t nbEnnemies;

	Player*  player;
	Text*    scoreLabel;
	Text*    timeLabel;
	Text*    gameOver;
	Text*    winLabel;

	bool hasDied;
	bool hasActivedGameOver;

	bool hasWon;
	bool hasActivedWin;

	int64_t  currentTime;
	int64_t  initTime;
	uint32_t score;

	Map*     map;
}InGame;

InGame*     InGame_create();
void        InGame_reinit(Context* self);
void        InGame_init(InGame* self);
EnumContext InGame_run(Context* self);
void        InGame_drawUI(InGame* self);
void        InGame_addScore(InGame* self, uint32_t score);
void        InGame_updateEnnemies(InGame* self);
void        InGame_updatePlayer(InGame* self);
void        InGame_updateCamera(InGame* self);
void        InGame_updateTime(InGame* self);
void        InGame_updateEvent(Context* context, SDL_Event* event);
void        InGame_loadMap(InGame* self, const char* path);
void        InGame_destroy(InGame* self);


#endif
