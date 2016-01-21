#include "MusicManager.h"

MusicManager* MusicManager_create()
{
	MusicManager* self = (MusicManager*)malloc(sizeof(MusicManager));
	if(self == NULL)
	{
		perror("Error in malloc \n");
		return NULL;
	}

	self->coin = Mix_LoadWAV("Resources/Sounds/coin.wav");
	self->jump = Mix_LoadWAV("Resources/Sounds/jump.wav");
	self->background = Mix_LoadMUS("Resources/Sounds/background.wav");
	printf("Mix_LoadWAV: %s\n", Mix_GetError());
	Mix_ExpireChannel(-1, 1000);

	return self;
}

void MusicManager_playSound(MusicManager* self, SoundEnum choice)
{
	switch(choice)
	{
		case COIN_SOUND:
			printf("%d \n", Mix_PlayChannel(-1, self->coin, 0));
			break;
		case JUMP:
			printf("%d \n", Mix_PlayChannel(-1, self->jump, 0));
			break;
	}
}

void MusicManager_stopBackground(MusicManager* self)
{
//	Mix_HaltMusic();
}

void MusicManager_playBackground(MusicManager* self)
{
//	Mix_PlayMusic(self->background, -1);
}
