#ifndef __waka_font_h__
#define __waka_font_h__
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "waka_graphics.h"
//Fonts et texte
typedef struct waka_font
{
    TTF_Font *sdl_font;
} waka_font;

waka_font waka_font_newfont(const char* path, int iSize);
void waka_font_freefont(waka_font font);
waka_texture waka_font_newtext(const char *text, waka_font font);
#endif