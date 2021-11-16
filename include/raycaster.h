#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <stddef.h>
#include "ray.h"
#include "color.h"
#include "primitive.h"

color raycaster_cast_ray(const ray* ray, const primitive* scene, const size_t scene_size, const int reflections);

#endif