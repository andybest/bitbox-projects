#pragma once

#include <stdbool.h>

typedef struct
{
    bool (*is_on_line)(int);
    bool (*draw_pixel)(int, int);
} Drawable;
