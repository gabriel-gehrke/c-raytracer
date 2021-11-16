#ifndef RAY_H
#define RAY_H
#include "float3.h"

struct _ray {
    float3 origin;
    float3 direction;
};
typedef struct _ray ray;

struct _ray_hit {
    float3 point;
    float3 normal;
    struct _primitive* object;
    float distance;
};
typedef struct _ray_hit ray_hit;


#endif