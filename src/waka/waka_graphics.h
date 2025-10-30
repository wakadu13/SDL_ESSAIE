#ifndef __waka_graphics_h__
#define __waka_graphics_h__
#include <stdbool.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
extern float waka_dt;//Delta time entre chaque frame
extern SDL_Renderer *waka_sdl_renderer;//Rendu SDL global
//Initialisation et fermeture de la SDL
int waka_graphics_init(const char *szTitle, int iWindowWidth, int iWindowHeight, int iGameWidth, int iGameHeight, bool bFullscreen);

void waka_graphics_close(void);//Ferme la SDL

//Gestion de la loop
int waka_graphics_begindraw(void);//Initialisation du dessin
void waka_graphics_enddraw(void);//Fin du dessin
//images
typedef struct waka_rectangle
{
    int x;
    int y;
    int w;
    int h;
}waka_rectangle;

typedef struct 
{
    int width;
    int height;
    SDL_Texture *sdl_texture;
}waka_texture;//Structure de texture

waka_texture waka_graphics_newimage(const char *path);//Charge une image et retourne une waka_texture
void waka_graphics_freeimage(waka_texture image);//Libere une image
void waka_graphics_draw(waka_texture image, int iX, int iY);//Dessine une image aux coordonnees iX, iY
void waka_graphics_drawQuad(waka_texture image, waka_rectangle rectSource, int iX, int iY);

//Primitives
void waka_graphics_setcolor(int iRed, int iGreen, int iBlue, int iAlpha);//Definit la couleur de dessin
void waka_graphics_line(int iX1, int iY1, int iX2, int iY2);//Dessine une ligne entre les points (iX1, iY1) et (iX2, iY2)
void waka_graphics_rectangle(const char*mode, int iX, int iY, int iW, int iH);//Dessine un rectangle aux coordonnees iX, iY de largeur iW et hauteur iH. Mode peut etre "line" ou "fill"


#endif