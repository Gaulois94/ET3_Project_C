#include "Contexts/Start.h"
#include "globalVar.h"

Start* Start_create()
{
	Start* self = (Start*)malloc(sizeof(Start));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}

	Start_init(self);
	return self;
}

void Start_init(Start* self)
{
	//Init text and buttons
	self->startText               = Text_create(NULL, globalVar_window, &WHITE, ResourcesManager_getData(globalVar_fonts, "dejavu"), "Start");
	self->optionText              = Text_create(NULL, globalVar_window, &WHITE, ResourcesManager_getData(globalVar_fonts, "dejavu"), "Option");
	self->quitText              = Text_create(NULL, globalVar_window, &WHITE, ResourcesManager_getData(globalVar_fonts, "dejavu"), "Quit");

    SDL_Rect r;
    r.x = 380;
    r.y = 200;
	self->startButton             = Button_create(NULL, NULL, &r, NULL, self->startText);

    r.x -= 5;
    r.y += 100;
	self->optionButton            = Button_create(NULL, NULL, &r, NULL, self->optionText);

    r.x += 10;
    r.y += 100;
	self->quitButton              = Button_create(NULL, NULL, &r, NULL, self->quitText);

	//!Set them static
	((Drawable*)self->startButton)->setStatic((Drawable*)self->startButton, true);
	((Drawable*)self->optionButton)->setStatic((Drawable*)self->optionButton, true);
	((Drawable*)self->quitButton)->setStatic((Drawable*)self->quitButton, true);

	//And set polymorphisme functions
	((Context*)self)->run         = &Start_run;
	((Context*)self)->updateEvent = &Start_updateEvent;
	((Context*)self)->reinit      = &Start_reinit;

	//Value of the next context
    self->nextContext             = NOTHING;
}

void Start_reinit(Context* context)
{
	//Reinit the window and the musique
	Start* self = (Start*)context;
	self->nextContext = NOTHING;
	Window_setCameraCoords(globalVar_window, 0, 0);
	MusicManager_setSound(globalVar_musics, false);
}

EnumContext Start_run(Context* context)
{
	//Just draw everything
	SDL_SetRenderDrawColor(globalVar_window->renderer, 0x00, 0x00, 0x00, 0xff);
    Start* self = (Start*)context;

    ((Drawable*)self->startButton)->draw((Drawable*)self->startButton, globalVar_window);
    ((Drawable*)self->optionButton)->draw((Drawable*)self->optionButton, globalVar_window);
    ((Drawable*)self->quitButton)->draw((Drawable*)self->quitButton, globalVar_window);

    return self->nextContext;
}

void Start_updateEvent(Context* context, SDL_Event* event)
{
    Start* self = (Start*)context;

	//Switch the button activated, we change the context
    if(Active_updateEvents((Active*)self->startButton, event))
    {
        self->nextContext = INGAME;
        return;
    }

    else if(Active_updateEvents((Active*)self->optionButton, event))
    {
        self->nextContext = OPTION;
        return;
    }

    else if(Active_updateEvents((Active*)self->quitButton, event))
    {
        self->nextContext = QUIT;
        return;
    }
}

void Start_destroy(Start* self)
{
	//And destroy everything
    ((Drawable*)self->quitButton)->destroy((Drawable*)self->quitButton);
    ((Drawable*)self->startButton)->destroy((Drawable*)self->startButton);
    ((Drawable*)self->optionButton)->destroy((Drawable*)self->optionButton);

    ((Drawable*)self->quitText)->destroy((Drawable*)self->quitText);
    ((Drawable*)self->startText)->destroy((Drawable*)self->startText);
    ((Drawable*)self->optionText)->destroy((Drawable*)self->optionText);

    free(self);
}
