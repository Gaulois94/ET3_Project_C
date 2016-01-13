#ifndef  INGAME_INC
#define  INGAME_INC

#include "Contexts/Context.h"
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
	Text*    score;
	Text*    timeLabel;

	int64_t  currentTime;
	int64_t  initTime;

	Map*     map;
}InGame;

InGame*     InGame_create();
void        InGame_init(InGame* self);
EnumContext InGame_run(Context* self);
void        InGame_drawUI(InGame* self);
void        InGame_updateEnnemies(InGame* self);
void        InGame_updatePlayer(InGame* self);
void        InGame_updateTime(InGame* self);
void        InGame_loadMap(InGame* self, const char* path);
void        InGame_destroy(InGame* self);


#endif
