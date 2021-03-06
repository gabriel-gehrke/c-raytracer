#ifndef FLOAT3_H
#define FLOAT3_H

#include <math.h>
#include <stdio.h>

typedef struct _float3 {
    float x, y, z;
} float3;

extern const float3 VEC_ZERO;
extern const float3 VEC_ONE;
extern const float3 VEC_UP;
extern const float3 VEC_DOWN;
extern const float3 VEC_FORW;
extern const float3 VEC_BACK;
extern const float3 VEC_LEFT;
extern const float3 VEC_RIGHT;

// calculates and returns the dot product of the given vectors
static inline float dot(float3 a, float3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// calculates and returns the length of the given vector
static inline float len(float3 v) {
    return sqrtf(dot(v, v));
}

// adds two given vectors and returns the sum
static inline float3 vadd(float3 a, float3 b) {
    float3 v = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
    return v; 
}

// subtracts the second vector from the first and returns the resulting vector
static inline float3 vsub(float3 a, float3 b) {
    float3 v = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
    return v; 
}

// multiply-accumulate for vectors: returns v = a + b * f
static inline float3 vmac(float3 a, float3 b, float f) {
    float3 v = {.x = a.x + b.x * f, .y = a.y + b.y * f, .z = a.z + b.z * f};
    return v; 
}

// multiplies the given vector by the given scalar and returns the result
static inline float3 vmul(float3 a, float f) {
    float3 v = {.x = a.x * f, .y = a.y * f, .z = a.z * f};
    return v; 
}

// calculates the distance between two given points in 3d space
static inline float vdist(float3 a, float3 b) {
    return len(vsub(a, b));
}

// calculates the squared distance between two given points in 3d space
static inline float vsqrdist(float3 a, float3 b) {
    float3 v = vsub(a, b);
    return dot(v, v);
}

// calculates and returns the cross product of the two given vectors
static inline float3 cross(float3 a, float3 b) {
    float3 v = {
        .x = a.y * b.z - a.z * b.y, 
        .y = a.z * b.x - a.x * b.z, 
        .z = a.x * b.y - a.y * b.x
    };
    return v; 
}

// returns the given vector in normalized form (with a length of 1)
static inline float3 normalized(float3 a) {
    float l = 1.0f / len(a);
    float3 v = {
        .x = a.x * l,
        .y = a.y * l,
        .z = a.z * l
    };
    return v;
}

// reflects a vector v off a surface with the given normal vector n and returns the resulting (normalized) vector
static inline float3 vreflect(float3 v, float3 n) {
    // r = v - 2*<n,v>*n
    return normalized(vsub(v, vmul(n, 2 * dot(n, v))));
}

static inline float3 vmin(float3 a, float3 b) {
    float3 v = {
        .x = fminf(a.x, b.x),
        .y = fminf(a.y, b.y),
        .z = fminf(a.z, b.z)
    };
    return v;
}

static inline float3 vmax(float3 a, float3 b) {
    float3 v = {
        .x = fmaxf(a.x, b.x),
        .y = fmaxf(a.y, b.y),
        .z = fmaxf(a.z, b.z)
    };
    return v;
}

// prints the string representation of the vector to the given stream
int vprint(float3 v, FILE* stream);

#endif
