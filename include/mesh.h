#ifndef MESH_H
#define MESH_H

#include "triangle.h"

struct _mesh {
    // the array of triangles making up this mesh
    triangle* tris;

    // the length of the triangles array
    size_t tris_len;
};
typedef struct _mesh mesh;

bool ray_mesh_intersection(const ray* r, const void* mesh_data, ray_hit* hit_out);
primitive mesh_get_primitive(mesh* m);

#endif