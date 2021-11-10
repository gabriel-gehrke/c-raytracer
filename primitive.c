#include "primitive.h"

bool primitive_get_intersection(const primitive* p, const ray* r, ray_hit* hit_out) {
    intersection_function f = p->intersector;
    return f(r, p->data, hit_out);
}
