#include "Contexts/Option.h"

Option* Option_create()
{
	Option* self = (Option*)malloc(sizeof(Option));
	if(self == NULL)
	{
		perror("Error in malloc");
		free(self);
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
	self->rightButton = Button_create(NULL, NULL, &rect, NULL, self->leftCommand);

	rect.x = 600;
	rect.y = 200;
	rect.w = 50;
	rect.h = 50;
	self->soundBox = CheckBox_create(NULL, NULL, &rect);

	return self;
}

EnumContext Option_run(Context* self)
{
	
}

void Option_updateEvent(Context* self, SDL_Event* event)
{

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

	free(option);
}
