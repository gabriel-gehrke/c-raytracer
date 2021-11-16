#ifndef RAY_H
#define RAY_H
#include "float3.h"

struct _ray {
    float3 origin;
    float3 direction;
};
typedef struct _ray ray;


#endif