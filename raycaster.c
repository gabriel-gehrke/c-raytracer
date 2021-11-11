#include "raycaster.h"

#define AMBIENT_LIGHT 0.1f

color raycaster_cast_ray(const ray* ray, const primitive* scene, size_t scene_size, int reflections) {
    float min_dist = INFINITY;
    primitive* closest = NULL;
    ray_hit hit;
    ray_hit closest_hit;
    
    for (size_t i = 0; i < scene_size; i++) {
        primitive* prim = &scene[i];

        if (primitive_get_intersection(prim, ray, &hit)) {
            min_dist = fminf(min_dist, hit.distance);
            closest = prim;
            closest_hit = *(&hit);
        }
    }

    // handle rays without any intersection
    if (!closest) return COLOR_BLACK;

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
            .origin = vmac(closest_hit.point, ray->direction, EPSILON),
            .direction = vreflect(ray->direction, closest_hit.normal)
        };
        color c_reflect = raycaster_cast_ray(&ray_reflected, scene, scene_size, reflections - 1);

        // average colors
        return color_avg(c_surface, c_reflect);
    }

    return c_surface;
}