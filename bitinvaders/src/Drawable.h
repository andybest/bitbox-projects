#pragma once

#include <stdbool.h>
#include <stdint.h>

#define NO_PIXEL 0x8000

typedef struct Drawable
{
    bool (*is_on_line)(struct Drawable*, int);
    uint16_t (*draw_pixel)(struct Drawable*, int, int);
} Drawable;
