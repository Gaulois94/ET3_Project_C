#ifndef  ACTIVE_INC
#define  ACTIVE_INC

#include "SDL2/SDL.h"
#include "typedefine.h"

typedef struct
{
	void(*activeCallback)(void* data);
	void(*disactiveCallback)(void* data);
	void* activeData;
	void* disactiveData;

	bool(*howActive)(Active*, const SDL_Event*);
	bool(*howDisactive)(Active*, const SDL_Event*);
	void(*activeIt)(Active*);
	void(*disActiveIt)(Active*);
	bool isActive;
}Active;

void Active_init(Active* self);
bool Active_update(Active* self, const SDL_Event* event);
void Active_activeIt(Active* self);
void Active_disactiveIt(Active* self);
bool Active_howActive(Active* self, const SDL_Event* event);
bool Active_howDisactive(Active* self, const SDL_Event* event);
void Active_setActiveFunc(Active* self, void(*callback)(void*));
void Active_setDisactiveFunc(Active* self, void(*callback)(void*));
void Active_setActiveData(Active* self, void* data);
void Active_setDisactiveData(Active* self, void* data);
bool Active_isActive(Active* self);

#endif
