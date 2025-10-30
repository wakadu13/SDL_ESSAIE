#include "SDL2/SDL.h"
#include "waka_keyboard.h"

waka_sdlkey _waka_keymap[] = {
    {"a", SDL_SCANCODE_A},
    {"b", SDL_SCANCODE_B},
    {"c", SDL_SCANCODE_C},
    {"d", SDL_SCANCODE_D},
    {"right", SDL_SCANCODE_RIGHT},
    {"left", SDL_SCANCODE_LEFT},
    {"up", SDL_SCANCODE_UP},
    {"down", SDL_SCANCODE_DOWN},
    {"z", SDL_SCANCODE_Z},
    {"q", SDL_SCANCODE_Q},
    {"s", SDL_SCANCODE_S},
    {"q", SDL_SCANCODE_Q},
    {"w", SDL_SCANCODE_W},
    {"e", SDL_SCANCODE_E},
    {"r", SDL_SCANCODE_R},
    {"t", SDL_SCANCODE_T},
    {"y", SDL_SCANCODE_Y},
    {"u", SDL_SCANCODE_U},
    {"i", SDL_SCANCODE_I},
    {"o", SDL_SCANCODE_O},
    {"p", SDL_SCANCODE_P},
    {"f", SDL_SCANCODE_F},
    {"space", SDL_SCANCODE_SPACE},
    {"return", SDL_SCANCODE_RETURN},
    {"escape", SDL_SCANCODE_ESCAPE},
};
const Uint8 *_waka_sdl_keystate;
waka_sdlkey *_key_search(const char *key)
{
    size_t num_items = sizeof(_waka_keymap)/sizeof(waka_sdlkey);
    for (size_t i = 0; i < num_items; i++)
    {
        if(strcmp(_waka_keymap[i].key, key) == 0)
        {
            return &_waka_keymap[i];
        }
    }
    return NULL;
}
void _waka_keyboard_init(void)
{
    _waka_sdl_keystate = SDL_GetKeyboardState(NULL);
}

bool waka_keyboard_isdown(const char *key)
{
    waka_sdlkey *found = _key_search(key);
    if(found){
        return _waka_sdl_keystate[found->sdl_scancode];
    }
    return NULL;
}