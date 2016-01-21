#ifndef  MUSICMANAGER_INC
#define  MUSICMANAGER_INC

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#ifndef WIN32
    #include <sys/types.h>
#endif

#define FADE_TIME 100

typedef enum 
{COIN_SOUND, JUMP}SoundEnum;

typedef struct
{
	Mix_Music* background;
	Mix_Chunk* coin;
	Mix_Chunk* jump;
}MusicManager;

MusicManager* MusicManager_create();
void MusicManager_playBackground(MusicManager* self);
void MusicManager_playSound(MusicManager* self, SoundEnum choice);
void MusicManager_stopBackground(MusicManager* self);
void MusicManager_clear(MusicManager* self);

#endif
