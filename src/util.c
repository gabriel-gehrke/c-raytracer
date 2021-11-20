#include "util.h"
#include "string.h"

float randf() {
    return 2.0f * (((float)rand())/((float)(RAND_MAX)) - 0.5f);
}

bool strequ(const char* a, const char* b) {
    while (*a != 0) {
        if (*a++ != *b++) {
            return false;
        }
    }
    return true;
}

bool strnequ(const char* a, const char* b, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (*a++ != *b++) {
            return false;
        }
    }
    return true;
}