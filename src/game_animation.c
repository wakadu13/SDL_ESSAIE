#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "waka/waka.h"
#include "waka/waka_graphics.h"
#include "waka/waka_font.h"
#include "game_animation.h"

animation anim_state[4];




void animation_setup(void)
{
    anim_state[WALK]= (animation){0,7,0.1f, true}; //(animation) sert a caster le resultat en type animation
    anim_state[IDLE] = (animation){12, 12, 0.0f,false};
    anim_state[FIRE] = (animation){8,11,0.2f, false};
    anim_state[FALL] = (animation){12, 16, 0.1f, false};

}

void animation_play(animStatus *status,indiana_animation anim)
{
    if (anim == status->currentAnimation)
    {
        return;
    }
    status->currentAnimation = anim;
    status->current_frame = anim_state[anim].first;
    }
void animation_update(animStatus *status)
{
    status->current_frame += anim_state[status->currentAnimation].speed;
    if(status->current_frame >= anim_state[status->currentAnimation].last + 1)
    {
        if (anim_state[status->currentAnimation].loop)
        {
            status->current_frame = anim_state[status->currentAnimation].first;
        }
        else
        {
        status->current_frame = anim_state[status->currentAnimation].last;
        }
    }
}
int animation_current_frame(animStatus *status)
{
    return (int)floor(status->current_frame);
}
void drawQuad(waka_texture *tex, int quadW, int quadH, int numFrame, int x, int y, bool FlipH, bool FlipV)
{
    waka_rectangle rect;
    rect.x = quadW*numFrame;
    rect.y = 0;
    rect.w = quadW;
    rect.h = quadH;
    waka_graphics_drawQuad(*tex, rect, x, y, FlipH, FlipV);
}
void animation_draw(waka_texture *tex, int quadW, int quadH, int x, int y, animStatus *status, bool FlipH, bool FlipV )
{
    drawQuad(tex, quadW, quadH, animation_current_frame(status), x, y, FlipH, FlipV );
}