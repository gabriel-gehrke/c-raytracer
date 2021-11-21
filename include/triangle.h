#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "float3.h"
#include "primitive.h"

struct _triangle
{
    float3 v0;
    float3 v1;
    float3 v2;

    float3 normal;
};
typedef struct _triangle triangle;


bool ray_triangle_intersection(const ray* r, const void* triangle_data, ray_hit* hit_out);
primitive triangle_get_primitive(triangle* t);

#endif