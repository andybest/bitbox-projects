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
