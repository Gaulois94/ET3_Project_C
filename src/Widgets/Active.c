#include "Widgets/Active.h"

void Active_init(Active* self)
{
	self->activeData = self->disactiveData = NULL;
	self->activeCallback = self->disactiveCallback = NULL;

	self->howActive = &Active_howActive;
	self->howDisactive = &Active_howDisactive;
	self->activeIt = &Active_activeIt;
	self->disactiveIt = &Active_disactiveIt;
	self->permanentActivated = false;
	self->isActive = false;
	self->update = &Active_update;

	self->autoDisactive = false;
}

void Active_update(Active* self)
{
	return;
}

bool Active_updateEvents(Active* self, const SDL_Event* event)
{
	bool returnValue = false;
	if(self->isActive)
	{
		if(!self->permanentActivated && self->howDisactive(self, event))
		{
			self->disactiveIt(self, event);
			returnValue = true;
		}
	}

	else
	{
		if(self->permanentActivated && (!self->isActive) || self->howActive(self, event))
		{
			self->activeIt(self, event);
			returnValue = true;
		}
	}

	if(self->autoDisactive)
		self->isActive = false;

	return returnValue;
}

void Active_activeIt(Active* self, const SDL_Event* e)
{
	self->isActive = true;
	if(self->activeCallback)
		self->activeCallback(self->activeData, self);
}

void Active_disactiveIt(Active* self, const SDL_Event* e)
{
	self->isActive = false;
	if(self->disactiveCallback)
		self->disactiveCallback(self->disactiveData, self);
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

void Active_setActiveFunc(Active* self, void(*func)(void*, Active*))
{
	self->activeCallback = func;
}

void Active_setActiveData(Active* self, void* data)
{
	self->activeData = data;
}

void Active_setDisactiveFunc(Active* self, void(*func)(void*, Active*))
{
	self->disactiveCallback = func;
}

void Active_setDisactiveData(Active* self, void* data)
{
	self->disactiveData = data;
}

void Active_setActive(Active* self, bool act)
{
	self->isActive = act;
}

bool Active_isActive(const Active* self)
{
	return self->isActive;
}
