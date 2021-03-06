#include "mesh.h"
#include "stdio.h"

bool ray_mesh_intersection(const ray* r, const void* mesh_data, ray_hit* hit_out) {
    const mesh* this = (mesh*) mesh_data;
    ray_hit closest = 
    {
        .object = NULL,
        .distance = INFINITY
    };

    const triangle* tris = this->tris;
    const size_t n = this->tris_len;

    // check intersection for every triangle in mesh
    for (size_t i = 0; i < n; i++) {
        ray_hit hit;
        if (ray_triangle_intersection(r, tris + i, &hit) && hit.distance < closest.distance) {
            closest = hit;
        }
    }

    if (!closest.object) return false;

    *hit_out = closest;
    return true;
}

primitive mesh_get_primitive(mesh* m) {
    primitive p = 
    {
        .data = m,
        .intersector = ray_mesh_intersection
    };
    return p;
}