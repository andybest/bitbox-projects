#include <bitbox.h>
#include "imageAssets.h"
#include "sprite.h"
#include <stdio.h>

Sprite *logo;
ASprite *invader;

bool right;
bool down;

void game_init() {
    logo = new_sprite_from_data(image_logo.pixels, image_logo.width, image_logo.height);
    invader = new_asprite_from_data(image_invader1.pixels, image_invader1.width, image_invader1.height / 4, 4);

    right = false;
    down = true;
}

void game_frame() {
    if(!right) {
        logo->x += 2;
        if(logo->x + logo->width >= 320) {
            right = true;
        }
    } else {
        logo->x -= 2;
        if(logo->x == 0) {
            right = false;
        }
    }
    
    if(down) {
        logo->y += 2;
        if(logo->y + logo->height >= 240) {
            down = false;
        }
    } else {
        logo->y -= 2;
        if(logo->y == 0) {
            down = true;
        }
    }

    if(vga_frame % 4 == 0)
        asprite_next_frame(invader);
}

void graph_frame() {
}

void graph_line() {
    // Clear to black
    memset(draw_buffer, 0x0F0F, sizeof(uint16_t) * 640);
    
    // We are halving the resolution
    int currentLine = vga_line / 2;

    Drawable *d = (Drawable *)&logo->drawable;

    if(sprite_is_on_line(logo, currentLine)) {
        for(int x = 0; x < 320; x++) {
            uint16_t p = logo->drawable.draw_pixel(logo, x, currentLine);
            if(p != NO_PIXEL) {
                draw_buffer[(x*2)] = p;
                draw_buffer[(x*2) + 1] = p;
            }
        }
    }

    Drawable *i = (Drawable *)invader;

    if(sprite_is_on_line(invader, currentLine)) {
        for(int x = 0; x < 320; x++) {
            uint16_t p = i->draw_pixel(invader, x, currentLine);
            if(p != NO_PIXEL) {
                draw_buffer[(x*2)] = p;
                draw_buffer[(x*2) + 1] = p;
            }
        }
    }
}
