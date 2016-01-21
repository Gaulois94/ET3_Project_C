#ifndef  MUSICMANAGER_INC
#define  MUSICMANAGER_INC

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#ifndef WIN32
    #include <sys/types.h>
#endif

typedef enum 
{COIN}SoundEnum;

typedef struct
{
	Mix_Music* background;
	Mix_Chunk* coin;
}MusicManager;

MusicManager* MusicManager_create();
void MusicManager_playIntro();

#endif
