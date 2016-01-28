#include "MusicManager.h"
#include "globalVar.h"

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
	MusicManager_playBackground(self);

	return self;
}

void MusicManager_playSound(MusicManager* self, SoundEnum choice)
{
	if(!globalVar_hasSound)
		return;
	switch(choice)
	{
		case COIN_SOUND:
			Mix_PlayChannel(-1, self->coin, 0);
			break;
		case JUMP:
			printf("%d \n", Mix_PlayChannel(-1, self->jump, 0));
			break;
	}
}

void MusicManager_stopBackground(MusicManager* self)
{
	Mix_HaltMusic();
}

void MusicManager_playBackground(MusicManager* self)
{
	if(globalVar_hasSound)
		Mix_PlayMusic(self->background, -1);
}

void MusicManager_setSound(MusicManager* self, bool sound)
{
	if(sound == false)
		MusicManager_stopBackground(self);
}

void MusicManager_destroy(MusicManager* self)
{
	Mix_FreeChunk(self->jump);
	Mix_FreeChunk(self->coin);
	Mix_FreeMusic(self->background);
	free(self);

}
