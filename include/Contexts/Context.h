#ifndef  CONTEXT_INC
#define  CONTEXT_INC

#include "globalVar.h"

typedef struct
{
	EnumContext(*run)(void);
}Context;

EnumContext Context_run();

#endif
