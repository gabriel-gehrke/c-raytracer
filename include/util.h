#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

// checks if two variables/structs are equal by comparing their size in bytes and performing a memcmp
#define EQUALS(A, B) ((sizeof(A) == sizeof(B)) && (memcmp(&A, &B, sizeof(A)) == 0))

typedef unsigned int uint;

// random float between -1 and 1
float randf();

bool strequ(const char* a, const char* b);

bool strnequ(const char* a, const char* b, size_t len);

#endif