#ifndef __waka_keyboard_h__
#define __waka_keyboard_h__
#include"SDL2/SDL.h"
#include <stdbool.h>
typedef struct waka_sdlkey
{
    char *key;
    SDL_Scancode sdl_scancode;
}waka_sdlkey;

extern const Uint8 *_waka_sdl_keystate;
void _waka_keyboard_init(void);
bool waka_keyboard_isdown(const char *key);
#endif