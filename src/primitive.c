#include "primitive.h"

bool primitive_get_intersection(const primitive* p, const ray* r, ray_hit* hit_out) {
    intersection_function func = p->intersector;
    bool intersects = func(r, p->data, hit_out);
    if (intersects) {
        hit_out->object = p;
    }
    return intersects;
}
