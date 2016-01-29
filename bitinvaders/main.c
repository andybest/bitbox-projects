#include <bitbox.h>
#include "imageAssets.h"

void game_init() {
}

void game_frame() {
}

void graph_frame() {
}

void graph_line() {

    if(vga_line < image_logo.height * 2)
    {
        const uint16_t *imagePtr = image_logo.pixels + (image_logo.width * (vga_line >> 1));

        for(int i = 0; i < image_logo.width; i++)
        {
            draw_buffer[(i << 1)] = imagePtr[i];
            draw_buffer[(i << 1) + 1] = imagePtr[i];
        }
    } else {
        for(int i = 0; i < 640; i++) {
            draw_buffer[i] = 0x0;
        }
    }
}
