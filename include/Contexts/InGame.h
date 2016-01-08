#ifndef  INGAME_INC
#define  INGAME_INC

#include "Context.h"

typedef struct
{
	Context  base;
	Ennemy** ennemies;
	uint32_t nbEnnemies;

	Map*     map;
}InGame

#endif
