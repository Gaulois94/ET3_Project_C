#ifndef  FINISH_INC
#define  FINISH_INC

#include "Objects/Object.h"

typedef struct
{
	Object base;
}Finish;

Object* Finish_create(uint32_t nbCasesX, uint32_t nbCasesY, uint32_t tileSizeX, uint32_t tileSizeY);

#endif
