#ifndef  START_INC
#define  START_INC

#include "Contexts/Context.h"
#include "Drawable/Text.h"
#include "Widgets/Button.h"

typedef struct
{
	Context base;

	EnumContext nextContext;
	Text* startText;
	Text* optionText;
	Text* quitText;
	Button* startButton;
	Button* optionButton;
	Button* quitButton;
}Start;

Start* Start_create();
void   Start_reinit(Context* context);
void   Start_init(Start* self);
EnumContext Start_run(Context* context);
void Start_updateEvent(Context* context, SDL_Event* event);
void Start_destroy(Start* self);

#endif
