# Framework Waka - Documentation

## Description
Waka est un framework de jeu 2D simple construit au-dessus de SDL2. Il fournit une API simplifiée pour la création de jeux en C.

## Modules

### Graphics (waka_graphics)
Module principal de rendu graphique.

#### Fonctions principales:
- `waka_graphics_init()` : Initialise la fenêtre et le renderer
  - Paramètres: titre, largeur/hauteur fenêtre, largeur/hauteur jeu, mode plein écran
  - Gère le redimensionnement et la mise à l'échelle

- `waka_graphics_draw()` : Dessine une texture à l'écran
  - Support de la transparence
  - Positionnement en x,y

- `waka_graphics_newimage()` : Charge une image (PNG/JPG)
- `waka_graphics_setcolor()` : Définit la couleur de dessin (RGBA)
- `waka_graphics_line()` : Dessine une ligne
- `waka_graphics_rectangle()` : Dessine un rectangle (plein ou vide)

### Font (waka_font)
Gestion du texte et des polices via SDL_ttf.

### Keyboard (waka_keyboard) 
Gestion des entrées clavier.

## Caractéristiques
- Support du redimensionnement de fenêtre
- Gestion de la transparence (alpha blending)
- Mise à l'échelle entière (pixel perfect)
- Limitation du framerate à 60 FPS
- Chargement d'images PNG et JPG
- Mode plein écran

## Utilisation basique
```c
// Initialisation
waka_graphics_init("Mon Jeu", 800, 600, 400, 300, false);

// Boucle principale
while(waka_graphics_begindraw()) {
    // Logique du jeu
    // Rendu graphique
    waka_graphics_enddraw();
}

// Nettoyage
waka_graphics_close();
```

## Notes techniques
- Utilise SDL2, SDL2_image et SDL2_ttf
- Support du VSync
- Accélération matérielle activée par défaut
- Taille de fenêtre minimale configurable