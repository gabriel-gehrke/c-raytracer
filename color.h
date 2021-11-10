#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

struct _color {
    uint8_t r, g, b;
};
typedef struct _color color;


const color COLOR_BLACK;
const color COLOR_WHITE;

color color_rand();
color color_mul(const color* c, float factor);

#endif