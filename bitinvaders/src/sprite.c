#include "sprite.h"
#include <stdlib.h>

Sprite *new_sprite()
{
    Sprite *s = malloc(sizeof(Sprite));

    s->x = 0;
    s->y = 0;
    s->width = 0;
    s->height = 0;

    s->ownsPixels = false;
}

bool sprite_is_on_line(Sprite *s, int lineNum)
{
    return s->y > lineNum && (s->y + s->height) < lineNum;
}

void sprite_draw_pixel(Sprite *s, int x, int y)
{

}

void delete_sprite(Sprite *s)
{
    if(s->ownsPixels)
        free(s->pixels);
    free(s);
}
