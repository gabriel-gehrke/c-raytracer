#include <stdlib.h>
#include "color.h"

const color COLOR_BLACK = {.r = 0, .g = 0, .b = 0};
const color COLOR_WHITE = {.r = 255, .g = 255, .b = 255};

color color_rand() {
    color c = {rand() % UINT8_MAX, rand() % UINT8_MAX, rand() % UINT8_MAX};
    return c;
}

color color_mul(const color* c, float factor) {
    color new_c = 
    {
        .r = (int) (c->r * factor),
        .g = (int) (c->g * factor),
        .b = (int) (c->b * factor)
    };

    return new_c;
}