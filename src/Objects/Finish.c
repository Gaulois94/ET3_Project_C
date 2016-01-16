#include "Objects/Finish.h"

Object* Finish_create(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY)
{
	Finish* finish = (Finish*)malloc(sizeof(Finish));
	if(finish == NULL)
		return NULL;
	Object_init((Object*)finish, nbCasesX, nbCasesY, tileSizeX, tileSizeY);
	return (Object*)finish;
}
