#include "Contexts/Option.h"
#include "globalVar.h"

Option* Option_create()
{
	Option* self = (Option*)malloc(sizeof(Option));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}

	//Init texts
	self->sound = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "SOUND");
	self->jump  = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "JUMP");
	self->left  = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "LEFT");
	self->right = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "RIGHT");
	self->quit  = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "QUIT");

	//Button texts
	self->jumpCommand = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "UP");
	self->leftCommand = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "LEFT");
	self->rightCommand = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "RIGHT");

	//Then place all the texts statement
	((Drawable*)self->sound)->setPosition((Drawable*)self->sound, 200, 100);
	((Drawable*)self->jump)->setPosition((Drawable*)self->jump, 200, 200);
	((Drawable*)self->left)->setPosition((Drawable*)self->left, 200, 300);
	((Drawable*)self->right)->setPosition((Drawable*)self->right, 200, 400);

	//Init buttons
	const SDL_Rect* commandRect = Drawable_getRect((Drawable*)self->jump);
	commandRect = Drawable_getRect((Drawable*)self->jumpCommand);
	SDL_Rect rect;
	rect.x = 600;
	rect.y = 200;
	rect.w = commandRect->w;
	rect.h = commandRect->h;
	self->jumpButton = Button_create(NULL, NULL, &rect, NULL, self->jumpCommand);

	commandRect = Drawable_getRect((Drawable*)self->leftCommand);
	rect.y += 100;
	rect.w = commandRect->w;
	rect.h = commandRect->h;
	self->leftButton = Button_create(NULL, NULL, &rect, NULL, self->leftCommand);

	commandRect = Drawable_getRect((Drawable*)self->rightCommand);
	rect.y += 100;
	rect.w = commandRect->w;
	rect.h = commandRect->h;
	self->rightButton = Button_create(NULL, NULL, &rect, NULL, self->rightCommand);

	rect.x = 600;
	rect.y = 100;
	rect.w = 50;
	rect.h = 50;
	self->soundBox = CheckBox_create(NULL, NULL, &rect); //Init the sound box

	commandRect = Drawable_getRect((Drawable*)self->rightCommand);
	rect.x = 350;
	rect.y = 500;
	rect.w = commandRect->w;
	rect.h = commandRect->h;
	self->quitButton = Button_create(NULL, NULL, &rect, NULL, self->quit);

	//Set all buttons callback
	Active_setActiveFunc((Active*)self->leftButton, Option_callback);
	Active_setActiveData((Active*)self->leftButton, (void*)self);

	Active_setActiveFunc((Active*)self->jumpButton, Option_callback);
	Active_setActiveData((Active*)self->jumpButton, (void*)self);

	Active_setActiveFunc((Active*)self->rightButton, Option_callback);
	Active_setActiveData((Active*)self->rightButton, (void*)self);

	self->actived = NULL;

	//Tap text (for entering a new value of key)
	self->tapCommand = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "Tap Command");

	//Set polymorphisme function
	((Context*)self)->reinit = &Option_reinit;
	((Context*)self)->run    = &Option_run;
	((Context*)self)->updateEvent = &Option_updateEvent;
	Option_reinit((Context*)self);

	self->quitOption = false;

	Active_setActive((Active*)self->soundBox, true);

	return self;
}

EnumContext Option_run(Context* context)
{
	SDL_SetRenderDrawColor(globalVar_window->renderer, 0x00, 0x00, 0x00, 0xff);
	//Just draw everything
	Option* self = (Option*)context;
	((Drawable*)self->left)->draw((Drawable*)self->left, globalVar_window);
	((Drawable*)self->right)->draw((Drawable*)self->right, globalVar_window);
	((Drawable*)self->jump)->draw((Drawable*)self->jump, globalVar_window);
	((Drawable*)self->sound)->draw((Drawable*)self->sound, globalVar_window);

	((Drawable*)self->leftButton)->draw((Drawable*)self->leftButton, globalVar_window);
	((Drawable*)self->rightButton)->draw((Drawable*)self->rightButton, globalVar_window);
	((Drawable*)self->jumpButton)->draw((Drawable*)self->jumpButton, globalVar_window);
	((Drawable*)self->quitButton)->draw((Drawable*)self->quitButton, globalVar_window);
	((Drawable*)self->soundBox)->draw((Drawable*)self->soundBox, globalVar_window);
	SDL_SetRenderDrawColor(globalVar_window->renderer, 0x00, 0x00, 0x00, 0xff);

	//And see if we are leaving this context
	if(self->quitOption)
		return START; //Return to the Start context
	return NOTHING;
}

void Option_reinit(Context* context)
{
	Option* self = (Option*)context;
	self->quitOption = false;
	//Stop the music
	MusicManager_stopBackground(globalVar_musics);

	//Reset all the buttons texts
	char text[20];

	Option_scancodeToString(text, globalVar_jumpscancode);
	Text_setText(self->jumpCommand, globalVar_window, text);

	Option_scancodeToString(text, globalVar_leftscancode);
	Text_setText(self->leftCommand, globalVar_window, text);

	Option_scancodeToString(text, globalVar_rightscancode);
	Text_setText(self->rightCommand, globalVar_window, text);

	Button_setText(self->jumpButton, self->jumpCommand, true);
	Button_setText(self->leftButton, self->leftCommand, true);
	Button_setText(self->rightButton, self->rightCommand, true);
	MusicManager_setSound(globalVar_musics, false);
}

void Option_updateEvent(Context* context, SDL_Event* event)
{
	Option* self = (Option*)context;

	//Give the event at all our buttons and sound box
	if(Active_updateEvents((Active*)self->jumpButton, event))
		return;
	else if(Active_updateEvents((Active*)self->leftButton, event))
		return;
	else if(Active_updateEvents((Active*)self->rightButton, event))
		return;
	else if(Active_updateEvents((Active*)self->soundBox, event))
	{
		globalVar_setSound(Active_isActive((Active*)self->soundBox));
		return;
	}
	else if(Active_updateEvents((Active*)self->quitButton, event))
	{
		self->quitOption = true;
		return;
	}

	//And see if we are changing the code of the button
	if(self->actived != NULL && event->type == SDL_KEYDOWN)
	{
		char text[20];

		Option_scancodeToString(text, event->key.keysym.scancode);

		if(self->actived == self->leftButton && event->key.keysym.scancode != globalVar_rightscancode && event->key.keysym.scancode != globalVar_jumpscancode)
		{
			Text_setText(self->leftCommand, globalVar_window, text);
			Button_setText(self->actived, self->leftCommand, true);
			globalVar_leftscancode = event->key.keysym.scancode;
			self->actived = NULL;
		}

		else if(self->actived == self->rightButton && event->key.keysym.scancode != globalVar_leftscancode && event->key.keysym.scancode != globalVar_jumpscancode)
		{
			Text_setText(self->rightCommand, globalVar_window, text);
			Button_setText(self->actived, self->rightCommand, true);
			globalVar_rightscancode = event->key.keysym.scancode;
			self->actived = NULL;
		}

		else if(self->actived == self->jumpButton && event->key.keysym.scancode != globalVar_rightscancode && event->key.keysym.scancode != globalVar_leftscancode)
		{
			Text_setText(self->jumpCommand, globalVar_window, text);
			Button_setText(self->actived, self->jumpCommand, true);
			globalVar_jumpscancode = event->key.keysym.scancode;
			self->actived = NULL;
		}
	}
}

void Option_scancodeToString(char* text, uint32_t scancode)
{
	switch(scancode)
	{
		case SDL_SCANCODE_LEFT:
			strcpy(text, "LEFT");
			break;

		case SDL_SCANCODE_RIGHT:
			strcpy(text, "RIGHT");
			break;

		case SDL_SCANCODE_UP:
			strcpy(text, "UP");
			break;

		case SDL_SCANCODE_DOWN:
			strcpy(text, "DOWN");
			break;

		case SDL_SCANCODE_KP_ENTER:
			strcpy(text, "ENTER");
			break;

		case SDL_SCANCODE_SPACE:
			strcpy(text, "SPACE");
			break;

		case SDL_SCANCODE_TAB:
			strcpy(text, "TAB");
			break;

		case SDL_SCANCODE_LCTRL:
		case SDL_SCANCODE_RCTRL:
			strcpy(text, "CTRL");
			break;

		case SDL_SCANCODE_LALT:
		case SDL_SCANCODE_RALT:
			strcpy(text, "ALT");
			break;

		case SDL_SCANCODE_LSHIFT:
		case SDL_SCANCODE_RSHIFT:
			strcpy(text, "Shift");
			break;

		default:
			//Transforme scancode to letters
			if(scancode >= 4 && scancode <= 30)
			{
				text[0] = 'A' - 4 + scancode;
				text[1] = '\0';
			}
			else
				text[0] = '\0';
			break;
	}
}

void Option_callback(void* option, Active* active)
{
	Option* self = (Option*)option;

	//Set the button text to tap command
	if(self->actived)
	{
		if(self->actived == self->leftButton)
			Button_setText(self->leftButton, self->leftCommand, true);

		else if(self->actived == self->rightButton)
			Button_setText(self->rightButton, self->rightCommand, true);

		else if(self->actived == self->jumpButton)
			Button_setText(self->jumpButton, self->jumpCommand, true);
	}

	self->actived = (Button*)active;
	Button_setText((Button*)active, self->tapCommand, true);
}

void Option_destroy(Option* option)
{
	//Destroy everything
	((Drawable*)option->sound)->destroy((Drawable*)option->sound);
	((Drawable*)option->jump)->destroy((Drawable*)option->jump);
	((Drawable*)option->left)->destroy((Drawable*)option->left);
	((Drawable*)option->right)->destroy((Drawable*)option->right);

	((Drawable*)option->jumpCommand)->destroy((Drawable*)option->jumpCommand);
	((Drawable*)option->leftCommand)->destroy((Drawable*)option->leftCommand);
	((Drawable*)option->rightCommand)->destroy((Drawable*)option->rightCommand);

	((Drawable*)option->jumpButton)->destroy((Drawable*)option->jumpButton);
	((Drawable*)option->leftButton)->destroy((Drawable*)option->leftButton);
	((Drawable*)option->rightButton)->destroy((Drawable*)option->rightButton);

	((Drawable*)option->soundBox)->destroy((Drawable*)option->soundBox);
	((Drawable*)option->tapCommand)->destroy((Drawable*)option->tapCommand);

	free(option);
}
