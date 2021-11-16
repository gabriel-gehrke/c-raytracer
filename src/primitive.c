#include "primitive.h"

bool primitive_get_intersection(const primitive* p, const ray* r, ray_hit* hit_out) {
    bool intersects = p->intersector(r, p->data, hit_out);
    if (intersects) {
        hit_out->object = p;
    }
    return intersects;
}
