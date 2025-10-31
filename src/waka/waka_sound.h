#ifndef __waka_audio_h__
#define __waka_audio_h__
#include <stdbool.h>
#include "SDL2/SDL_mixer.h"

typedef struct { Mix_Chunk *chunk; } waka_sound;
typedef struct { Mix_Music *music; } waka_music;

/* Système */
bool waka_audio_init(int freq, int channels, int chunksize);
/* Appelle ceci avant de quitter l'app (après avoir libéré sons/musiques) */
void waka_audio_close(void);

/* Sons courts (SFX) */
waka_sound  waka_audio_loadsound(const char *path);
void        waka_audio_freesound(waka_sound s);
int         waka_audio_playsound(waka_sound s, int loops /*0=une fois, -1=boucle*/, int channel /*-1=auto*/, int volume /*0..128*/);

/* Musiques longues (streaming) */
waka_music  waka_audio_loadmusic(const char *path);
void        waka_audio_freemusic(waka_music m);
bool        waka_audio_playmusic(waka_music m, int loops /*-1=boucle*/);
void        waka_audio_haltmusic(void);
void        waka_audio_setmusicvolume(int volume /*0..128*/);

/* Pause/Resume global */
void        waka_audio_pauseall(void);
void        waka_audio_resumeall(void);

#endif
