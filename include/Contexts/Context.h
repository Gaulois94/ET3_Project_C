#ifndef  CONTEXT_INC
#define  CONTEXT_INC

#include "globalVar.h"

typedef struct Context
{
	EnumContext(*run)(struct Context*);
	void(*updateEvent)(struct Context*, SDL_Event*);
}Context;

EnumContext Context_run(Context* self);
void Context_updateEvent(Context* self, SDL_Event* event;);

#endif
