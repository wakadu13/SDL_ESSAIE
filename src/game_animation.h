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
void animation_init(void);
void animation_play(indiana_animation anim);
void animation_update(void);
int animation_current_frame(void);
void animation_draw(waka_texture *tex, int quadW, int quadH, int x, int y );

void drawQuad(waka_texture *tex, int quadW, int quadH, int numFrame, int x, int y);



#endif