#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "waka/waka.h"
#include "waka/waka_graphics.h"
#include "waka/waka_font.h"
#include "waka/waka_keyboard.h"
#include "waka/waka_sound.h"
#include "game.h"
#include "game_animation.h"


waka_font font;
waka_texture texTitle;
waka_texture texIndiana;
waka_rectangle indianaPlayer;
animStatus IndiaP;
waka_sound sonPong;
void game_init(void)
{
   font = waka_font_newfont("gfx/PixelMaster.ttf", 25);
   texTitle = waka_font_newtext("Mini duel by wakadu13", font);
   texIndiana = waka_graphics_newimage("gfx/indiana.png");
   indianaPlayer.x =10; 
   indianaPlayer.y=10; 
   indianaPlayer.w=25; 
   indianaPlayer.h=24;
   animation_setup();
   animation_play(&IndiaP, IDLE);
    sonPong = waka_audio_loadsound("gfx/perd.wav");
}
void game_reset(void)
{
    animation_play(&IndiaP, IDLE);
}
void game_update(float dt)
{
    bool isMove=false;
    animation_update(&IndiaP);
    if (waka_keyboard_isdown("f"))
    {
        animation_play(&IndiaP,FIRE);
        waka_audio_playsound(sonPong, 1, 1, 240);
    }
    if (waka_keyboard_isdown("up"))
    {
        animation_play(&IndiaP,WALK);
        indianaPlayer.y -= 1;
        isMove = true;
    }
    if (waka_keyboard_isdown("down"))
    {
        animation_play(&IndiaP,WALK);
        indianaPlayer.y += 1;
        isMove = true;
    }
    if (waka_keyboard_isdown("right"))
    {
        animation_play(&IndiaP,WALK);
        indianaPlayer.x += 1;
        isMove = true;
    }
    if (waka_keyboard_isdown("left"))
    {
        animation_play(&IndiaP,WALK);
        indianaPlayer.x -= 1;
        isMove = true;
    }
    if(!(isMove || waka_keyboard_isdown("f")))
    {
        animation_play(&IndiaP,IDLE);
    }

    
}

void game_draw(void)
{
    waka_graphics_draw(texTitle, 1, 1);
    animation_draw(&texIndiana, indianaPlayer.w, indianaPlayer.h, indianaPlayer.x, indianaPlayer.y, &IndiaP, true, true);
   
}
void game_close(void)
{
    waka_audio_freesound(sonPong);
    waka_graphics_freeimage(texIndiana);
    waka_graphics_freeimage(texTitle);
    waka_font_freefont(font);
}