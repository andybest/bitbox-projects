#include "sprite.h"
#include <stdlib.h>
#include <stdio.h>

Sprite *new_sprite()
{
    Sprite *s = malloc(sizeof(Sprite));
    sprite_init(s);

    return s;
}

void sprite_init(Sprite *s) {
    s->x = 0;
    s->y = 0;
    s->width = 0;
    s->height = 0;

    s->ownsPixels = false;

    s->drawable.is_on_line = (bool (*)(Drawable*, int))sprite_is_on_line;
    s->drawable.draw_pixel = (uint16_t (*)(Drawable*, int, int))sprite_draw_pixel;
}

Sprite *new_sprite_from_data(uint16_t *pixels, int width, int height)
{
    Sprite *s = new_sprite();
    s->width = width;
    s->height = height;
    s->pixels = pixels;
    s->ownsPixels = false;

    return s;
}

bool sprite_is_on_line(Sprite *s, int lineNum)
{
    bool rv = s->y <= lineNum && (s->y + s->height) > lineNum;
    return rv;
}

uint16_t sprite_draw_pixel(Sprite *s, int x, int y)
{
    // Check if pixel is within bounding box
    if(x < s->x || x > (s->x + s->width)) {
        return NO_PIXEL;
    }
    
    int idx = (x - s->x) + ((y - s->y) * s->width);
    return s->pixels[idx];
}

void delete_sprite(Sprite *s)
{
    if(s->ownsPixels)
        free(s->pixels);
    free(s);
}

ASprite *new_asprite() {
    ASprite *s = malloc(sizeof(ASprite));
    sprite_init(&s->sprite);
    s->numFrames = 0;
    s->currentFrame = 0;
    s->sprite.drawable.draw_pixel = (uint16_t (*)(Drawable*, int, int))asprite_draw_pixel;

    return s;
}

ASprite *new_asprite_from_data(uint16_t *pixels, int width, int height, int numFrames) {
    ASprite *s = new_asprite();
    s->sprite.width = width;
    s->sprite.height = height;
    s->sprite.pixels = pixels;
    s->sprite.ownsPixels = false;
    s->numFrames = numFrames;

    return s;
}

uint16_t asprite_draw_pixel(ASprite *s, int x, int y)
{
    // Check if pixel is within bounding box
    if(x < s->sprite.x || x > (s->sprite.x + s->sprite.width)) {
        return NO_PIXEL;
    }
    
    int idx = (x - s->sprite.x) + ((y - s->sprite.y) * s->sprite.width);
    return s->sprite.pixels[idx + (s->sprite.width * s->sprite.height * s->currentFrame)];
}

void asprite_next_frame(ASprite *s) {
    if(s->numFrames > 0) {
        s->currentFrame++;
        s->currentFrame %= s->numFrames;
    }
}
