#pragma once

#include <stdint.h>

typedef struct RGB555Image {
    uint16_t width, height;
    const uint16_t *pixels;
} RGB555Image;

const struct RGB555Image image_logo;
