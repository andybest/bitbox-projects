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
void sprite_init(Sprite *s);
bool sprite_is_on_line(Sprite *s, int lineNum);
uint16_t sprite_draw_pixel(Sprite *s, int x, int y);


/*
 * Animated sprite
 */
typedef struct {
    Sprite sprite;
    
    int numFrames;
    int currentFrame;
} ASprite;

ASprite *new_asprite();
ASprite *new_asprite_from_data(uint16_t *pixels, int width, int height, int numFrames);
uint16_t asprite_draw_pixel(ASprite *s, int x, int y);
void asprite_next_frame(ASprite *s);
