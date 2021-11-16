#ifndef FLOAT3_H
#define FLOAT3_H

#include <math.h>

typedef struct _float3 {
    float x, y, z;
} float3;

// definitions elsewhere
const float3 VEC_ZERO;
const float3 VEC_ONE;
const float3 VEC_UP;
const float3 VEC_DOWN;
const float3 VEC_FORW;
const float3 VEC_BACK;
const float3 VEC_LEFT;
const float3 VEC_RIGHT;

static inline float dot(float3 a, float3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline float len(float3 v) {
    return sqrtf(dot(v, v));
}

static inline float3 vadd(float3 a, float3 b) {
    float3 v = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
    return v; 
}

static inline float3 vsub(float3 a, float3 b) {
    float3 v = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
    return v; 
}

static inline float3 vmac(float3 a, float3 b, float f) {
    float3 v = {.x = a.x + b.x * f, .y = a.y + b.y * f, .z = a.z + b.z * f};
    return v; 
}

static inline float3 vmul(float3 a, float f) {
    float3 v = {.x = a.x * f, .y = a.y * f, .z = a.z * f};
    return v; 
}

static inline float vdist(float3 a, float3 b) {
    return len(vsub(a, b));
}

static inline float vsqrdist(float3 a, float3 b) {
    float3 v = vsub(a, b);
    return dot(v, v);
}


static inline float3 cross(float3 a, float3 b) {
    float3 v = {
        .x = a.y * b.z - a.z * b.y, 
        .y = a.z * b.x - a.x * b.z, 
        .z = a.x * b.y - a.y * b.x
    };
    return v; 
}

static inline float3 normalized(float3 a) {
    float l = 1.0f / len(a);
    float3 v = {
        .x = a.x * l,
        .y = a.y * l,
        .z = a.z * l
    };
    return v;
}

static inline float3 vreflect(float3 v, float3 n) {
    // r = v - 2*<n,v>*n
    return normalized(vsub(v, vmul(n, 2 * dot(n, v))));
}

#endif