#ifndef  CONTEXT_INC
#define  CONTEXT_INC

#include "GlobalVar.h"

typedef struct
{
	(EnumContext)(*run)(GlobalVar*);
}Context;

EnumContext Context_run(GlobalVar* globalVar);

#endif
