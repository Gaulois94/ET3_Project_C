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
	Text* quit;

	Button* jumpButton;
	Button* leftButton;
	Button* rightButton;
	Button* quitButton;

	Button* actived;

	CheckBox* soundBox;


	bool quitOption;
}Option;

Option* Option_create();
EnumContext Option_run(Context* self);
void Option_reinit(Context* self);
void Option_scancodeToString(char* text, uint32_t scancode);
void Option_updateEvent(Context* self, SDL_Event* event);
void Option_destroy(Option* self);
void Option_callback(void* option, Active* self);

#endif
