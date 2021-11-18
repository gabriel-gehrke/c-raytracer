#include "util.h"

float randf() {
    return 2.0f * (((float)rand())/((float)(RAND_MAX)) - 0.5f);
}