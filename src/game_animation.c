#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "waka/waka.h"
#include "waka/waka_graphics.h"
#include "waka/waka_font.h"
#include "game_animation.h"

animation anim_state[4];


animStatus IndiaP;

void animation_setup(void)
{
    anim_state[WALK]= (animation){0,7,0.1f, true}; //(animation) sert a caster le resultat en type animation
    anim_state[IDLE] = (animation){12, 12, 0.0f,false};
    anim_state[FIRE] = (animation){8,11,0.2f, false};
    anim_state[FALL] = (animation){12, 16, 0.1f, false};
    IndiaP.current_frame =  0.0f;

}

void animation_init(void)
{
    IndiaP.currentAnimation = IDLE;
    IndiaP.current_frame = anim_state[IndiaP.currentAnimation].first;
}

void animation_play(indiana_animation anim)
{
    if (anim == IndiaP.currentAnimation)
    {
        return;
    }
    IndiaP.currentAnimation = anim;
    IndiaP.current_frame = anim_state[IndiaP.currentAnimation].first;
    }
void animation_update(void)
{
    IndiaP.current_frame += anim_state[IndiaP.currentAnimation].speed;
    if(IndiaP.current_frame >= anim_state[IndiaP.currentAnimation].last + 1)
    {
        if (anim_state[IndiaP.currentAnimation].loop)
        {
            IndiaP.current_frame = anim_state[IndiaP.currentAnimation].first;
        }
        else
        {
        IndiaP.current_frame = anim_state[IndiaP.currentAnimation].last;
        }
    }
}
int animation_current_frame(void)
{
    return (int)floor(IndiaP.current_frame);
}
void drawQuad(waka_texture *tex, int quadW, int quadH, int numFrame, int x, int y)
{
    waka_rectangle rect;
    rect.x = quadW*numFrame;
    rect.y = 0;
    rect.w = quadW;
    rect.h = quadH;
    waka_graphics_drawQuad(*tex, rect, x, y);
}
void animation_draw(waka_texture *tex, int quadW, int quadH, int x, int y )
{
    drawQuad(tex, quadW, quadH, animation_current_frame(), x, y);
}