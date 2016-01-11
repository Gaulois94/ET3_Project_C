#ifndef  CONTEXT_INC
#define  CONTEXT_INC

#include "globalVar.h"

typedef struct Context
{
	EnumContext(*run)(struct Context*);
}Context;

EnumContext Context_run(Context* self);

#endif
