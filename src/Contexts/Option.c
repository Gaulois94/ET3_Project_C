#include "Contexts/Option.h"

Option* Option_create()
{
	Option* self = (Option*)malloc(sizeof(Option));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}

	self->sound = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "SOUND");
	self->jump = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "JUMP");
	self->left = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "LEFT");
	self->right = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "RIGHT");

	self->jumpCommand = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "UP");
	self->leftCommand = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "LEFT");
	self->rightCommand = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "RIGHT");

	((Drawable*)self->sound)->setPosition((Drawable*)self->sound, 200, 200);
	((Drawable*)self->jump)->setPosition((Drawable*)self->jump, 200, 300);
	((Drawable*)self->left)->setPosition((Drawable*)self->left, 200, 400);
	((Drawable*)self->right)->setPosition((Drawable*)self->right, 200, 500);

	const SDL_Rect* commandRect = Drawable_getRect((Drawable*)self->jump);
	commandRect = Drawable_getRect((Drawable*)self->jumpCommand);
	SDL_Rect rect;
	rect.x = 600;
	rect.y = 300;
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
	rect.y = 200;
	rect.w = 50;
	rect.h = 50;
	self->soundBox = CheckBox_create(NULL, NULL, &rect);

	Active_setActiveFunc((Active*)self->leftButton, Option_callback);
	Active_setActiveData((Active*)self->leftButton, (void*)self);

	Active_setActiveFunc((Active*)self->jumpButton, Option_callback);
	Active_setActiveData((Active*)self->jumpButton, (void*)self);

	Active_setActiveFunc((Active*)self->rightButton, Option_callback);
	Active_setActiveData((Active*)self->rightButton, (void*)self);

	self->actived = NULL;

	self->tapCommand = Text_create(NULL, globalVar_window, &WHITE, (TTF_Font*)ResourcesManager_getData(globalVar_fonts, "dejavu"), "Tap Command");

	((Context*)self)->reinit = &Option_reinit;
	((Context*)self)->run    = &Option_run;
	((Context*)self)->updateEvent = &Option_updateEvent;
	Option_reinit((Context*)self);

	return self;
}

EnumContext Option_run(Context* context)
{
	SDL_SetRenderDrawColor(globalVar_window->renderer, 0x00, 0x00, 0x00, 0xff);
	Option* self = (Option*)context;
	((Drawable*)self->left)->draw((Drawable*)self->left, globalVar_window);
	((Drawable*)self->right)->draw((Drawable*)self->right, globalVar_window);
	((Drawable*)self->jump)->draw((Drawable*)self->jump, globalVar_window);
	((Drawable*)self->sound)->draw((Drawable*)self->sound, globalVar_window);

	((Drawable*)self->leftButton)->draw((Drawable*)self->leftButton, globalVar_window);
	((Drawable*)self->rightButton)->draw((Drawable*)self->rightButton, globalVar_window);
	((Drawable*)self->jumpButton)->draw((Drawable*)self->jumpButton, globalVar_window);
	((Drawable*)self->soundBox)->draw((Drawable*)self->soundBox, globalVar_window);
	SDL_SetRenderDrawColor(globalVar_window->renderer, 0x00, 0x00, 0x00, 0xff);
}

void Option_reinit(Context* context)
{
	MusicManager_stopBackground(globalVar_musics);
}

void Option_updateEvent(Context* context, SDL_Event* event)
{
	Option* self = (Option*)context;

	if(Active_updateEvents((Active*)self->jumpButton, event))
		return;
	else if(Active_updateEvents((Active*)self->leftButton, event))
		return;
	else if(Active_updateEvents((Active*)self->rightButton, event))
		return;
	else if(Active_updateEvents((Active*)self->soundBox, event))
		return;

	if(self->actived != NULL && event->type == SDL_KEYDOWN)
	{
		char text[20];

		switch(event->key.keysym.scancode)
		{
			case SDL_SCANCODE_LEFT:
				strcpy(text, "LEFT");
				break;

			case SDL_SCANCODE_RIGHT:
				strcpy(text, "LEFT");
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
				if(event->key.keysym.scancode >= 4 && event->key.keysym.scancode <= 30)
				{
					text[0] = 'A' - 4 + event->key.keysym.scancode;
					text[1] = '\0';
				}
				break;
		}

		if(self->actived == self->leftButton)
		{
			Text_setText(self->leftCommand, globalVar_window, text);
			Button_setText(self->actived, self->leftCommand, true);
		}

		else if(self->actived == self->rightButton)
		{
			Text_setText(self->rightCommand, globalVar_window, text);
			Button_setText(self->actived, self->rightCommand, true);
		}

		else if(self->actived == self->jumpButton)
		{
			Text_setText(self->jumpCommand, globalVar_window, text);
			Button_setText(self->actived, self->jumpCommand, true);
		}
		self->actived = NULL;
	}

}

void Option_callback(void* option, Active* active)
{
	Option* self = (Option*)option;

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
