#ifndef MESH_H
#define MESH_H

#include "triangle.h"

struct _mesh {
    triangle* tris;
    size_t tris_len;
};
typedef struct _mesh mesh;

bool ray_mesh_intersection(const ray* r, void* mesh_data, ray_hit* hit_out);
primitive mesh_get_primitive(mesh* m);

#endif