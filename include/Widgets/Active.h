#ifndef  ACTIVE_INC
#define  ACTIVE_INC

#include "SDL2/SDL.h"
#include "typedefine.h"
#include "Window.h"

typedef struct Active
{
	void(*activeCallback)(void* data, struct Active*);
	void(*disactiveCallback)(void* data, struct Active*);
	void* activeData;
	void* disactiveData;

	bool(*howActive)(struct Active*, const SDL_Event*);
	bool(*howDisactive)(struct Active*, const SDL_Event*);
	void(*activeIt)(struct Active*, const SDL_Event*);
	void(*disactiveIt)(struct Active*, const SDL_Event*);
	void(*update)(struct Active*);
	bool isActive;
	bool autoDisactive;
	bool permanentActivated;
}Active;

void Active_init(Active* self);
/** \brief Fonction update. Use to update the Active
 * \param self the active itself*/
void Active_update(Active* self);

/** \brief update the active with an event. It calls howActive, howDisactive and activeIt / disactiveIt if the how functions returns true.
 * \param self the Active itself
 * \param event the SDL::Event to take in consideration. It is passed to howActive, howDisactive, activeIt and disactiveIt
 * \return the object has catch the SDL_Event or not*/
bool Active_updateEvents(Active* self, const SDL_Event* event);

/** \brief function called if the Active need to be actived.
 * \param self the Active itself
 * \param event the SDL_Event which has actived the object*/
void Active_activeIt(Active* self, const SDL_Event* event);

/** \brief function called if the Active need to be disactived.
 * \param self the Active itself
 * \param event the SDL_Event which has disactived the object*/
void Active_disactiveIt(Active* self, const SDL_Event* event);

/** \brief function called when the object has received an event. It tells how the Active object has to be actived
 * \param self the Active itself
 * \param event the SDL_Event to respond to
 * \return the function has to be actived or not*/
bool Active_howActive(Active* self, const SDL_Event* event);

/** \brief function called when the object has received an event. It tells how the Active object has to be disactived
 * \param self the Active itself
 * \param event the SDL_Event to respond to
 * \return the function has to be disactived or not*/
bool Active_howDisactive(Active* self, const SDL_Event* event);

/** \brief set the active callback with its data to pass
 * \param self the Active itself
 * \param callback the callback function*/
void Active_setActiveFunc(Active* self, void(*callback)(void*, Active*));

/** \brief set the disactive callback with its data to pass
 * \param self the Active itself
 * \param callback the callback function*/
void Active_setDisactiveFunc(Active* self, void(*callback)(void*, Active*));

/** \brief set the active data bound to the callback to pass when the object is actived
 * \param self the Active itself
 * \param data the data to pass to the callback function*/
void Active_setActiveData(Active* self, void* data);

/** \brief set the disactive data bound to the callback to pass when the object is disactived
 * \param self the Active itself
 * \param data the data to pass to the callback function*/
void Active_setDisactiveData(Active* self, void* data);

/** \brief set whether the Active object is actived or not
 * \param self the Active itself
 * \param act the value of the Active object.*/
void Active_setActive(Active* self, bool act);

/** \brief the Active object is actived or not 
 *  \return the Active object is actived or not */
bool Active_isActive(const Active* self);

#endif
