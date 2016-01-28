#ifndef  MUSICMANAGER_INC
#define  MUSICMANAGER_INC

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "typedefine.h"
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
void MusicManager_setSound(MusicManager* self, bool sound);
void MusicManager_destroy(MusicManager* self);

#endif
