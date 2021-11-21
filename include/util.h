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

// checks if two strings are equal
bool strequ(const char* a, const char* b);

// checks if two strings are equal, checking only for the first "len" characters
bool strnequ(const char* a, const char* b, size_t len);

// counts the number of occurences of a substring in a string (not overlapping)
size_t strncountstr(const char* str, const char* substr, size_t limit);

#endif