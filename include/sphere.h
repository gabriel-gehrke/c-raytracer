#ifndef SPHERE_H
#define SPHERE_H

#include "float3.h"
#include "ray.h"
#include "primitive.h"

struct _sphere {
    float3 center;
    float radius;
};
typedef struct _sphere sphere;

bool ray_sphere_intersection(const ray* r, const void* sphere_data, ray_hit* hit_out);
primitive sphere_get_primitive(sphere* s);

#endif