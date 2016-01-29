#pragma once

#include "drawable.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    Drawable drawable;
    int x;
    int y;
    int width;
    int height;

    bool ownsPixels;
    uint16_t *pixels;
} Sprite;

Sprite *new_sprite();
Sprite *new_sprite_from_data(uint16_t *pixels, int width, int height);
bool sprite_is_on_line(Sprite *s, int lineNum);
uint16_t sprite_draw_pixel(Sprite *s, int x, int y);
