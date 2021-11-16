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
        .r = (uint8_t) (c.r * factor),
        .g = (uint8_t) (c.g * factor),
        .b = (uint8_t) (c.b * factor)
    };

    return new_c;
}

// averages two given colors and returns the new color
static inline color color_avg(const color a, const color b) {
    color c =
    {
        .r = (uint8_t) (((uint32_t)a.r + (uint32_t)b.r) / 2),
        .g = (uint8_t) (((uint32_t)a.g + (uint32_t)b.g) / 2),
        .b = (uint8_t) (((uint32_t)a.b + (uint32_t)b.b) / 2)
    };
    return c;
}

#endif