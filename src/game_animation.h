#ifndef __waka_animation_h__
#define __waka_animation_h__
#include <stdbool.h>
typedef struct animation
{
    int first;
    int last;
    float speed;
    bool loop;
}animation;

typedef enum indiana_animation
{
    WALK = 0,
    IDLE,
    FIRE,
    FALL
}indiana_animation;

typedef struct animStatus
{
    indiana_animation currentAnimation;
    float current_frame;
}animStatus;


void animation_play(animStatus *status,indiana_animation anim);
void animation_update(animStatus *status);
int animation_current_frame(animStatus *status);
void animation_draw(waka_texture *tex, int quadW, int quadH, int x, int y,animStatus *status , bool FlipH, bool FlipV);

void drawQuad(waka_texture *tex, int quadW, int quadH, int numFrame, int x, int y, bool FlipH, bool FlipV);
void animation_setup(void);


#endif