#ifndef OPTION_INC
#define OPTION_INC

#include "Contexts/Context.h"
#include "Drawable/Text.h"
#include "Widgets/Button.h"
#include "Widgets/CheckBox.h"

typedef struct
{
	Context base;

	Text* sound;
	Text* jump;
	Text* left;
	Text* right;
	Text* jumpCommand;
	Text* leftCommand;
	Text* rightCommand;

	Text* tapCommand;

	Button* jumpButton;
	Button* leftButton;
	Button* rightButton;

	Button* actived;

	CheckBox* soundBox;
}Option;

Option* Option_create();
EnumContext Option_run(Context* self);
void Option_reinit(Context* self);
void Option_updateEvent(Context* self, SDL_Event* event);
void Option_destroy(Option* self);
void Option_callback(void* option, Active* self);

#endif
