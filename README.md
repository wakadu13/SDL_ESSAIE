# Waka Framework

A lightweight 2D game framework built on top of SDL2, designed for creating simple games in C.

## Features

- Simple and straightforward API
- Window management with resizing support
- Hardware-accelerated rendering with VSync
- Pixel-perfect integer scaling
- Transparency support (alpha blending)
- Image loading (PNG/JPG)
- TTF font rendering
- Keyboard input handling
- Frame rate limiting (60 FPS)
- Fullscreen support

## Dependencies

- SDL2
- SDL2_image
- SDL2_ttf

## Getting Started

### Basic Example

```c
#include "waka/waka.h"
#include "waka/waka_graphics.h"

int main(int argc, char **argv) 
{
    // Initialize with window size 800x600 and game resolution 400x300
    waka_init();
    waka_graphics_init("My Game", 800, 600, 400, 300, false);
    
    // Game loop
    while(waka_graphics_begindraw()) 
    {
        // Handle input
        if(waka_keyboard_isdown("escape")) {
            break;
        }
        
        // Update game logic
        
        // Render
        waka_graphics_enddraw();
    }
    
    // Cleanup
    waka_graphics_close();
    return 0;
}
