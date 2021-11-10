#pragma once
#include <stddef.h>
#include "float3.h"
#include "color.h"
#include "primitive.h"

#define PI 3.14159265358979323846

struct _camera {
    float3 position;
    float3 forward;
    float3 upward;
    float3 right;
    float focus;
};
typedef struct _camera camera;

void camera_set_fov(camera* cam, float fov);

void camera_render(const camera* cam, color* pixels, int width, int height, const primitive* scene, size_t scene_size);