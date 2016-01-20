#include <bitbox.h>
#include <math.h>

#define TEX_WIDTH 256
#define TEX_HEIGHT 256

#define TEX_PIXEL(x, y) (x ^ y)

int shiftX, shiftY;
float animX, animY;

void game_init() {
    shiftX = shiftY = 0;
}

void game_frame() {
    animX += 0.5;
    animY += 0.5;
}

void graph_frame() {

}

void graph_line8() {}

void graph_line() {
    int y = vga_line >> 1;

    shiftX = (int)animX;
    shiftY = (int)animY;

    for(int x=0; x < 320; x++) {
        int angle, distance;
        float ratio = 32.0;

        float iX = x - 320 / 2.0;
        float iY = y - 240 / 2.0;
        distance = (int)(ratio * TEX_HEIGHT / sqrt(iX * iX + iY * iY)) % TEX_HEIGHT;
        angle = (unsigned int)(0.5 * TEX_WIDTH * atan2(y - 240 / 2.0, x - 320 / 2.0) / 3.1416);

        uint8_t color = TEX_PIXEL((unsigned int)(distance + shiftX) % TEX_WIDTH, (unsigned int)(angle + shiftY) % TEX_HEIGHT);
        draw_buffer[x << 1] = color;
        draw_buffer[(x << 1) + 1] = color;
    }
}
