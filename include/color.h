#ifndef COLOR_H
#define COLOR_H

#include <stdlib.h>
#include <stdint.h>

struct _color {
    uint8_t r, g, b;
};
typedef struct _color color;


const color COLOR_BLACK;
const color COLOR_WHITE;

// generates a random color
static inline color color_rand() {
    color c = {rand() % UINT8_MAX, rand() % UINT8_MAX, rand() % UINT8_MAX};
    return c;
}

// multiplies a given color's rgb values with a given factor and returns the new color
static inline color color_mul(const color c, const float factor) {
    color new_c = 
    {
        .r = (int) (c.r * factor),
        .g = (int) (c.g * factor),
        .b = (int) (c.b * factor)
    };

    return new_c;
}

// averages two given colors and returns the new color
static inline color color_avg(const color a, const color b) {
    color c =
    {
        .r = (uint8_t) (((int)a.r + (int)b.r) / 2),
        .g = (uint8_t) (((int)a.g + (int)b.g) / 2),
        .b = (uint8_t) (((int)a.b + (int)b.b) / 2)
    };
    return c;
}

#endif