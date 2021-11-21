#include "util.h"
#include "string.h"

float randf() {
    return 2.0f * (((float)rand())/((float)(RAND_MAX)) - 0.5f);
}

bool strequ(const char* a, const char* b) {
    while (*a != '\0' && *a++ == *b++);
    return *a == *b;
}

bool strnequ(const char* a, const char* b, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (*a == 0 || *b == 0 || *a++ != *b++) {
            return false;
        }
    }
    return true;
}

size_t strncountstr(const char* str, const char* substr, size_t limit) {
    size_t count = 0;
    const size_t substr_len = strlen(substr);
    limit -= substr_len;

    for (size_t i = 0; i < limit; i++) {
        if (memcmp(str + i, substr, substr_len) == 0) {
            count++;
            i += substr_len;
        }
    }

    return count;
}