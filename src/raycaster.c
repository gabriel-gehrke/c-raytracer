#include "raycaster.h"
#include "stdio.h"
#include <math.h>

#define AMBIENT_LIGHT 0.2f
#define SKY_COLOR COLOR_WHITE

color raycaster_cast_ray(const ray* ray, const primitive* scene, const size_t scene_size, const uint reflections) {
    ray_hit closest = {
        .object = NULL,
        .distance = INFINITY
    };
    
    for (size_t i = 0; i < scene_size; i++) {
        ray_hit hit;
        bool hit_by_ray = primitive_get_intersection(&scene[i], ray, &hit);

        if (hit_by_ray && hit.distance <= closest.distance) {
            closest = hit;
        }
    }

    // handle rays without any intersection
    primitive* obj = closest.object;
    if (obj == NULL) return SKY_COLOR;

    // very basic shading based on surface normal
    const float3 normal = closest.normal;
    const float3 lightDir = VEC_DOWN;
    float cosTheta = fmaxf(AMBIENT_LIGHT, fminf(1, -dot(normal, lightDir)));
    color c_surface = color_mul(obj->color, cosTheta);

    // handle reflections
    if (reflections == 0) return c_surface;

    // create reflected ray
    struct _ray ray_reflected = 
    {
        .origin = vmac(closest.point, ray->direction, -EPSILON), // minus because we need to retract from the hit point
        .direction = vreflect(ray->direction, normal)
    };
    color c_reflect = raycaster_cast_ray(&ray_reflected, scene, scene_size, reflections - 1);

    // average colors
    return color_avg(c_surface, c_reflect);
}