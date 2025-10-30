#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "waka/waka.h"
#include "waka/waka_graphics.h"
#include "waka/waka_font.h"
#include "game.h"
/*
gcc -g src/main.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -o bin/monprogramme 
bin/monprogramme.exe  
  */
// Fonction de chargement de texture methode 1

int main (int argc, char **argv)
{
	
	// Pour afficher les printf en temps reel
	setvbuf(stdout, NULL, _IONBF, 0);
	// Debut du programme
	int GameWidth = 320, GameHeight = 200;
	int WindowWidth = 640, WindowHeight = 400;
// Initialisation de la SDL
	waka_init();
	waka_graphics_init("Mon test SDL2", WindowWidth, WindowHeight, GameWidth, GameHeight, false);

	
// Boucle d'evenements
	game_init();
	while(true)
	{
		
		// Creation de la variable evenement
		if(waka_graphics_begindraw() == 0 || waka_keyboard_isdown("escape"))
		{
			break;
		}
		game_update(waka_dt);
		game_draw();




		waka_graphics_enddraw();
	
	}

	waka_graphics_close();
	// Retour sans erreur
	return 0;
}