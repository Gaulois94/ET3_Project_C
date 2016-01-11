#include "Widgets/Active.h"

void Active_init(Active* self)
{
	self->activeData = self->disactiveData = NULL;
	self->activeCallback = self->disactiveCallback = NULL;

	self->howActive = &Active_howActive;
	self->howDisactive = &Active_howDisactive;
}

bool Active_update(Active* self, const SDL_Event* event)
{
	bool active = self->isActive;
	if(active)
		if(howDisactive())
			self->disactiveIt(self);

	else
		if(permanentActivated && (!self->isActive) || self->howActive(self, event))
			self->activeIt(self);

	return active != self->isActive;
}

void Active_activeIt(Active* self)
{
	self->isActive = true;
}

void Active_disactiveIt(Active* self)
{
	self->isActive = false;
}

bool Active_howActive(Active* self, const SDL_Event* event)
{
	return false;
}

bool Active_howDisactive(Active* self, const SDL_Event* event)
{
	return false;
}

void Active_setPermanentActivation(Active* self, bool act)
{
	self->permanentActivated = act;
}

void Active_setActiveFunc(Active* self, void(*func)(void*))
{
	self->activeCallback = func;
}

void Active_setActiveData(Active* self, void* data)
{
	self->activeData = data;
}

void Active_setDisactiveFunc(Active* self, void(*func)(void*))
{
	self->disactiveFunc = func;
}

void Active_setDisactiveData(Active* self, void* data)
{
	self->disactiveData = data;
}

void Active_isActive(Active* self)
{
	return self->isActive;
}
