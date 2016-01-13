#include "Widgets/Active.h"

void Active_init(Active* self)
{
	self->activeData = self->disactiveData = NULL;
	self->activeCallback = self->disactiveCallback = NULL;

	self->howActive = &Active_howActive;
	self->howDisactive = &Active_howDisactive;
}

bool Active_updateEvents(Active* self, const SDL_Event* event)
{
	bool active = self->isActive;
	if(active)
		if(!self->permanentActivated && self->howDisactive(self, event))
			self->disactiveIt(self);

	else
		if(self->permanentActivated && (!self->isActive) || self->howActive(self, event))
			self->activeIt(self);

	return active != self->isActive;
}

void Active_activeIt(Active* self)
{
	self->isActive = true;
	if(self->activeCallback)
		self->activeCallback(self->activeData);
}

void Active_disactiveIt(Active* self)
{
	self->isActive = false;
	if(self->disactiveCallback)
		self->disactiveCallback(self->disactiveData);
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
	self->disactiveCallback = func;
}

void Active_setDisactiveData(Active* self, void* data)
{
	self->disactiveData = data;
}

bool Active_isActive(const Active* self)
{
	return self->isActive;
}
