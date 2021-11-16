#include "raycaster.h"

#define AMBIENT_LIGHT 0.5f
#define SKY_COLOR COLOR_WHITE

color raycaster_cast_ray(const ray* ray, const primitive* scene, const size_t scene_size, const int reflections) {
    ray_hit closest_hit = {
        .object = NULL,
        .distance = INFINITY
    };
    
    for (size_t i = 0; i < scene_size; i++) {
        ray_hit hit;

        if (primitive_get_intersection(scene + i, ray, &hit) && hit.distance < closest_hit.distance) {
            closest_hit = hit;
        }
    }

    // handle rays without any intersection
    primitive* closest = closest_hit.object;
    if (!closest) return SKY_COLOR;

    color c_surface = closest->color;

    // very basic shading based on surface normal
    const float3 lightDir = VEC_DOWN;
    float cosTheta = fmaxf(AMBIENT_LIGHT, fminf(1, -dot(closest_hit.normal, lightDir)));
    c_surface = color_mul(c_surface, cosTheta);

    // handle reflections
    if (reflections > 0) {

        // create reflected ray
        struct _ray ray_reflected = 
        {
            .origin = vmac(closest_hit.point, ray->direction, 1e-3f),
            .direction = vreflect(ray->direction, closest_hit.normal)
        };
        color c_reflect = raycaster_cast_ray(&ray_reflected, scene, scene_size, reflections - 1);

        // average colors
        return color_avg(c_surface, c_reflect);
    }

    return c_surface;
}