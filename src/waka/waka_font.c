#include <assert.h>
#include "waka_font.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "waka_graphics.h"

waka_font waka_font_newfont(const char* path, int iSize)
{
	waka_font font = {NULL};
	font.sdl_font = TTF_OpenFont(path, iSize);
	if(font.sdl_font == NULL)
	{
		printf("Unable to create font %s Error %s\n",path, TTF_GetError());
	}
	return font;
}
void waka_font_freefont(waka_font font)
{
	TTF_CloseFont(font.sdl_font);
}
waka_texture waka_font_newtext(const char *text, waka_font font)
{
	assert(font.sdl_font != NULL);
	waka_texture tex;
	tex.sdl_texture = NULL;

	SDL_Surface *surface;
	SDL_Color texcolor = {255, 255, 255, 255};

	surface = TTF_RenderUTF8_Solid(font.sdl_font, text, texcolor);
	tex.sdl_texture = SDL_CreateTextureFromSurface(waka_sdl_renderer, surface);
	tex.width = surface->w;
	tex.height = surface->h;
	
	SDL_FreeSurface(surface);

	return tex;

}