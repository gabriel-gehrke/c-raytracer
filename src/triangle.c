#include "triangle.h"

bool ray_triangle_intersection(const ray* r, const void* triangle_data, ray_hit* hit_out) {
    const triangle* this = (triangle*) triangle_data;
    float3 n = this->normal;

    // backface culling: don't render the triangle if it is hit from behind (dot product is positive)
    float D = dot(r->direction, n);
    if (D < -EPSILON) return false;

    float3 v0 = this->v0;
    float3 v1 = this->v1;
    float3 v2 = this->v2;

    // calculate intersection point on triangle plane
    float t = dot(vsub(v0, r->origin), n) / D;
    float3 hit = vmac(r->origin, r->direction, t);

    // check if point is inside triangle
    float3 a = cross(vsub(v1, v0), vsub(hit, v0));
    if (dot(n, a) < -1e-5) return false;

    float3 b = cross(vsub(v2, v1), vsub(hit, v1));
    if (dot(n, b) < -1e-5) return false;

    float3 c = cross(vsub(v0, v2), vsub(hit, v2));
    if (dot(n, c) < -1e-5) return false;

    /*
    Vector3d edges[] = {v1 - v0, v2 - v1, v0 - v2, hit - v0, hit - v1, hit - v2};
    for (int i = 0; i < 3; i++) {
        Vector3d c = crossProduct(edges[i], edges[i + 3]);
        if (dotProduct(n, c) < 0) return false;
    }
    */

    hit_out->distance = t;
    hit_out->normal = n;
    hit_out->point = hit;
    return true;
}

primitive triangle_get_primitive(triangle* t) {
    primitive p = 
    {
        .data = t,
        .intersector = ray_triangle_intersection
    };

    return p;
}