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





# Waka Framework API Reference

## Table of Contents
- [Graphics](#graphics)
- [Font](#font)
- [Keyboard](#keyboard)
- [Game Animation](#game-animation)
- [Core](#core)

## Graphics
### Window Management
```c
void waka_graphics_init(const char* title, int window_width, int window_height, 
                       int game_width, int game_height, bool fullscreen)
```
Initializes the graphics system with specified window and game resolution.
- `title`: Window title
- `window_width/height`: Physical window dimensions
- `game_width/height`: Internal game resolution
- `fullscreen`: Enable/disable fullscreen mode

```c
bool waka_graphics_begindraw(void)
```
Begins a new frame, clears the screen. Returns false if window should close.

```c
void waka_graphics_enddraw(void)
```
Finalizes frame rendering and presents to screen.

### Drawing Functions
```c
void waka_graphics_draw_rect(int x, int y, int width, int height, uint32_t color)
```
Draws a filled rectangle at (x,y) with specified dimensions and color.

```c
void waka_graphics_draw_line(int x1, int y1, int x2, int y2, uint32_t color)
```
Draws a line between two points with specified color.

```c
void waka_graphics_set_color(uint32_t color)
```
Sets the current drawing color (RGBA format).

## Font
```c
WakaFont* waka_font_load(const char* filename, int size)
```
Loads a TTF font file with specified point size.

```c
void waka_font_draw_text(WakaFont* font, const char* text, int x, int y, uint32_t color)
```
Renders text using specified font at (x,y) position with given color.

## Keyboard
```c
bool waka_keyboard_isdown(const char* key)
```
Checks if specified key is currently pressed.
- Common keys: "up", "down", "left", "right", "space", "escape"

```c
bool waka_keyboard_waspressed(const char* key)
```
Returns true if key was pressed this frame.

## Game Animation
```c
Animation* create_animation(int frame_count, int frame_duration)
```
Creates a new animation with specified number of frames and duration per frame.

```c
void update_animation(Animation* anim)
```
Updates animation state, advances frames if needed.

```c
void draw_animation(Animation* anim, int x, int y)
```
Draws current frame of animation at specified position.

## Core
```c
void waka_init(void)
```
Initializes the Waka framework core systems.

```c
void waka_close(void)
```
Shuts down framework and frees resources.

## Memory Management
```c
void* waka_malloc(size_t size)
```
Allocates memory with integrated error checking.

```c
void waka_free(void* ptr)
```
Safely frees allocated memory.

## Error Handling
```c
void waka_set_error(const char* message)
```
Sets error message for framework.

```c
const char* waka_get_error(void)
```
Returns last error message or NULL if no error.

## Notes
- All coordinates are relative to game resolution, not window size
- Colors use RGBA format (0xRRGGBBAA)
- Memory allocated by framework functions must be freed with waka_free()
- Check waka_get_error() after operations that might fail
