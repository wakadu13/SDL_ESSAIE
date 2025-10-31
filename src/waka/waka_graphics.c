#include <stdio.h>
#include <assert.h>
#include "waka_graphics.h"

#define SDL_ASSERT_LEVEL 2

SDL_Window *waka_sdl_window;
SDL_Renderer *waka_sdl_renderer;

int _waka_alpha = 255;
float waka_dt = 0;
Uint32 _waka_framestart = 0;
 
int waka_GameWidth = 0;
int waka_GameHeight = 0;

int waka_graphics_init(const char *szTitle, int iWindowWidth, int iWindowHeight, int iGameWidth, int iGameHeight, bool bFullscreen)
{
    if(SDL_Init(SDL_INIT_EVERYTHING)	!= 0)
	{
		return -1;
	}
    // Creation de la fenetre
    Uint32 iFlags = SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE;
    if(bFullscreen) iFlags |= SDL_WINDOW_FULLSCREEN;
	waka_sdl_window = SDL_CreateWindow(
		szTitle, 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		iWindowWidth,
		iWindowHeight,
	    iFlags);
    // Verification de la creation de la fenetre
	if (waka_sdl_window == NULL)
	{
		printf("Impossible de generer la fenetre! Error : %s\n", SDL_GetError());
		return -1;
	}
    // Creation du rendu
	waka_sdl_renderer = SDL_CreateRenderer(waka_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // Verification de la creation du rendu	
	if(waka_sdl_renderer == NULL)
	{
		printf("Impossible de generer le rendu! Error : %s\n",SDL_GetError());
		return -1;
	}
	else
	{
		// Initialisation de la SDL image
		int imgFlags = IMG_INIT_PNG|IMG_INIT_JPG;
		if(!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL image n'a pas demarer! SDL_image error : %s\n", IMG_GetError());
			return -1;
		}
	}
	if(TTF_Init()==-1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",TTF_GetError());
	}

    SDL_SetWindowMinimumSize(waka_sdl_window, iGameWidth, iGameHeight);//Pour eviter d'avoir une fenetre trop petite
    SDL_RenderSetLogicalSize(waka_sdl_renderer, iGameWidth, iGameHeight);//Pour gerer le redimensionnement
    SDL_SetRenderDrawBlendMode(waka_sdl_renderer, SDL_BLENDMODE_BLEND);//Pour gerer la transparence
    SDL_RenderSetIntegerScale(waka_sdl_renderer, SDL_TRUE); //Ne lisse pas donc utile pour du pixel art
    waka_GameWidth = iGameWidth;
    waka_GameHeight = iGameHeight;
    
    return 0;
}


void waka_graphics_close(void)
{
    // Destruction des elements SDL
    SDL_DestroyRenderer(waka_sdl_renderer);
    SDL_DestroyWindow(waka_sdl_window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

int waka_graphics_begindraw()
{
    Uint32 now = SDL_GetTicks();
    waka_dt = now - _waka_framestart;
    waka_dt = (float)(waka_dt/1000.0);
    _waka_framestart = now;

    SDL_Event event;
		
		if(SDL_PollEvent(&event))
		{
			// Gestion de la fermeture de la fenetre
			if(event.type == SDL_QUIT) 
			{
				return 0;
			}
			
		}
        SDL_RenderClear(waka_sdl_renderer);
    return 1;
}
void waka_graphics_enddraw(void)
{
    SDL_RenderPresent(waka_sdl_renderer);
    //Limit framerate
    int frameTime = SDL_GetTicks() - _waka_framestart;
    if (frameTime < (1000/60))
    {
        int delay = (1000/60) - frameTime;
        if(delay > 0)
        {
            SDL_Delay(delay);
        }
    }
}


waka_texture waka_graphics_newimage(const char *path)
{
    waka_texture tex;
	tex.sdl_texture = NULL;
    tex.sdl_texture = IMG_LoadTexture(waka_sdl_renderer, path);
    if(tex.sdl_texture == NULL)
    {
        printf("Unable to load texture from %s Error : %s", path, IMG_GetError());
    }
    else
    {
        SDL_QueryTexture(tex.sdl_texture, NULL, NULL, &tex.width, &tex.height);
    }
    return tex;
}

void waka_graphics_freeimage(waka_texture image)
{
    if(image.sdl_texture != NULL)
    {
        SDL_DestroyTexture(image.sdl_texture);
        image.sdl_texture = NULL;
    }
}
void waka_graphics_draw(waka_texture image, int iX, int iY)
{
    SDL_Rect rectDest;
    rectDest.x = iX;
    rectDest.y = iY;
    rectDest.w = image.width;
    rectDest.h = image.height;

    SDL_SetTextureAlphaMod(image.sdl_texture, _waka_alpha); //Pour modifier la transparence de l'image
    int iResult = SDL_RenderCopyEx(waka_sdl_renderer, image.sdl_texture, NULL, &rectDest, 0, NULL, SDL_FLIP_NONE);
    if (iResult != 0)
    {
        printf("Unable to draw texture  Error : %s", IMG_GetError());
        return;
    }
}
void waka_graphics_drawQuad(waka_texture image, waka_rectangle pRectSource, int iX, int iY, bool FlipH, bool FlipV)
{
    SDL_Rect rectSource;
    rectSource.x = pRectSource.x;
    rectSource.y = pRectSource.y;
    rectSource.w = pRectSource.w;
    rectSource.h = pRectSource.h;

    SDL_Rect rectDest;
    rectDest.x = iX;
    rectDest.y = iY;
    rectDest.w = rectSource.w;
    rectDest.h = rectSource.h;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(FlipH) flip = SDL_FLIP_HORIZONTAL;
    if(FlipV) flip = SDL_FLIP_VERTICAL;
    SDL_SetTextureAlphaMod(image.sdl_texture, _waka_alpha); //Pour modifier la transparence de l'image
    int iResult = SDL_RenderCopyEx(waka_sdl_renderer, image.sdl_texture,&rectSource, &rectDest, 0, NULL, flip);
    if (iResult != 0)
    {
        printf("Unable to draw texture  Error : %s", IMG_GetError());
        return;
    }    
}

void waka_graphics_setcolor(int iRed, int iGreen, int iBlue, int iAlpha)
{
    SDL_SetRenderDrawColor(waka_sdl_renderer, iRed, iGreen, iBlue, iAlpha);
    _waka_alpha = iAlpha;
}
void waka_graphics_line(int iX1, int iY1, int iX2, int iY2)
{
    SDL_RenderDrawLine(waka_sdl_renderer, iX1,  iY1, iX2, iY2);
}

void waka_graphics_rectangle(const char*mode, int iX, int iY, int iW, int iH)
{
    SDL_Rect rect;
    rect.x = iX;
    rect.y = iY;
    rect.w = iW;
    rect.h = iH;

    if (strcmp(mode, "line") == 0)
    {
        SDL_RenderDrawRect(waka_sdl_renderer, &rect);
    }
    else if (strcmp(mode, "fill") == 0)
    {
        SDL_RenderFillRect(waka_sdl_renderer, &rect);
    }
}

