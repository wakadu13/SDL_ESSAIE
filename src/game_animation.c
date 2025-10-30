#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "waka/waka.h"
#include "waka/waka_graphics.h"
#include "waka/waka_font.h"
#include "game_animation.h"

animation anim_state[4] = {
    {0,7,0.1f, true},
    {12, 12, 0.0f,false},
    {8,11,0.2f, false},
    {12, 16, 0.1f, false}
};

indiana_animation currentAnimation;

float current_frame = 0.0f;

void animation_init(void)
{
    currentAnimation = IDLE;
    current_frame = anim_state[currentAnimation].first;
}
void animation_play(indiana_animation anim)
{
    if (anim == currentAnimation)
    {
        return;
    }
    currentAnimation = anim;
    current_frame = anim_state[currentAnimation].first;
    }
void animation_update(void)
{
    current_frame += anim_state[currentAnimation].speed;
    if(current_frame >= anim_state[currentAnimation].last + 1)
    {
        if (anim_state[currentAnimation].loop)
        {
            current_frame = anim_state[currentAnimation].first;
        }
        else
        {
        current_frame = anim_state[currentAnimation].last;
        }
    }
}
int animation_current_frame(void)
{
    return (int)floor(current_frame);
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