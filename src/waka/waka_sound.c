#include "waka_sound.h"
#include <stdio.h>

bool waka_audio_init(int freq, int channels, int chunksize) {
    if (Mix_OpenAudio(freq, MIX_DEFAULT_FORMAT, channels, chunksize) < 0) {
        fprintf(stderr, "Mix_OpenAudio: %s\n", Mix_GetError());
        return false;
    }
    int flags = MIX_INIT_OGG | MIX_INIT_MP3 ;
    if ((Mix_Init(flags) & flags) != flags) {
        /* Pas bloquant: on log seulement si certains formats manquent */
        fprintf(stderr, "Mix_Init partial: %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(32); /* assez pour petits jeux */
    return true;
}

void waka_audio_close(void) {
    Mix_HaltChannel(-1);
    Mix_HaltMusic();
    Mix_CloseAudio();
    Mix_Quit();
}

/* --------- SFX --------- */

waka_sound waka_audio_loadsound(const char *path) {
    waka_sound s = {0};
    s.chunk = Mix_LoadWAV(path);
    if (!s.chunk) fprintf(stderr, "LoadSFX %s: %s\n", path, Mix_GetError());
    return s;
}

void waka_audio_freesound(waka_sound s) {
    if (s.chunk) Mix_FreeChunk(s.chunk);
}

int waka_audio_playsound(waka_sound s, int loops, int channel, int volume) {
    if (!s.chunk) return -1;
    if (volume >= 0) Mix_VolumeChunk(s.chunk, volume);
    return Mix_PlayChannel(channel, s.chunk, loops);
}

/* --------- Music --------- */

waka_music waka_audio_loadmusic(const char *path) {
    waka_music m = {0};
    m.music = Mix_LoadMUS(path);
    if (!m.music) fprintf(stderr, "LoadMusic %s: %s\n", path, Mix_GetError());
    return m;
}

void waka_audio_freemusic(waka_music m) {
    if (m.music) Mix_FreeMusic(m.music);
}

bool waka_audio_playmusic(waka_music m, int loops) {
    if (!m.music) return false;
    if (Mix_PlayMusic(m.music, loops) < 0) {
        fprintf(stderr, "PlayMusic: %s\n", Mix_GetError());
        return false;
    }
    return true;
}

void waka_audio_haltmusic(void) { Mix_HaltMusic(); }
void waka_audio_setmusicvolume(int volume) { Mix_VolumeMusic(volume); }

/* --------- Global pause/resume --------- */

void waka_audio_pauseall(void) {
    Mix_Pause(-1);   /* pause all channels */
    Mix_PauseMusic();
}

void waka_audio_resumeall(void) {
    Mix_Resume(-1);
    Mix_ResumeMusic();
}
