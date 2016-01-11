#ifndef  INGAME_INC
#define  INGAME_INC

#include "Contexts/Context.h"
#include "Ennemy.h"
#include "Player.h"

typedef struct
{
	Context  base;

	Ennemy** ennemies;
	uint32_t nbEnnemies;

	Player*  player;

	Map*     map;
}InGame

InGame*     InGame_create();
void        InGame_init(InGame* self);
EnumContext InGame_run(Context* self);
void        InGame_updateEnnemies(InGame* self);
void        InGame_updatePlayer(InGame* self);
void        InGame_loadMap(InGame* self, const char* path);
void        InGame_destroy(InGame* self);


#endif
