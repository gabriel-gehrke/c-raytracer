#include "sphere.h"
#include <math.h>

primitive sphere_get_primitive(sphere* s) {
    primitive p = 
    {
        .intersector = ray_sphere_intersection,
        .data = s
    };
    return p;
}

bool ray_sphere_intersection(const ray* ray, const void* data, ray_hit* hit_out) {
    const sphere* this = (sphere*) data;

    float3 d = ray->direction;
    float3 o = vsub(ray->origin, this->center);
    float r = this->radius;

    float A = dot(d, d);
    float B = 2.0f * dot(d, o);
    float C = dot(o, o) - r*r;

    // check if ray hits the sphere
    float discr = B*B - 4*A*C;
    if (discr < EPSILON) return false;

    // correct numerical unstability
    float s = sqrtf(discr);
    float q = -0.5f * (B < 0.0f ? B - s : B + s); 
  
    float t0 = q / A;
    float t1 = C / q;

    float t = fminf(t0, t1);
    if (t < 0) return false;

    const float3 hit = vmac(ray->origin, ray->direction, t);

    hit_out->distance = t;
    hit_out->point = hit;
    hit_out->normal = normalized(vsub(hit, this->center));
    return true;
}