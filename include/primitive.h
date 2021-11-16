#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#define EPSILON ((float) 1e-6)

#include <stdbool.h>
#include "float3.h"
#include "color.h"
#include "ray.h"

struct _ray_hit {
    float3 point;
    float3 normal;
    struct _primitive* object;
    float distance;
};
typedef struct _ray_hit ray_hit;

typedef bool (*intersection_function)(const ray*, void*, ray_hit*);

struct _primitive {
    intersection_function intersector;
    void* data;
    color color;
};
typedef struct _primitive primitive;


bool primitive_get_intersection(const primitive* p, const ray* r, ray_hit* hit_out);

#endif