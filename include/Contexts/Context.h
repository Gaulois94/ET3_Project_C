#ifndef  CONTEXT_INC
#define  CONTEXT_INC

#include "SDL2/SDL.h"

typedef enum
{
	NOTHING,
	START,
	INGAME,
	OPTION,
	QUIT
}EnumContext;

typedef struct Context
{
	void(*reinit)(struct Context*);
	EnumContext(*run)(struct Context*);
	void(*updateEvent)(struct Context*, SDL_Event*);
}Context;

EnumContext Context_run(Context* self);
void Context_updateEvent(Context* self, SDL_Event* event);
void Context_reinit(Context* self);

#endif
