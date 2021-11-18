#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <stddef.h>
#include <stdbool.h>
#include "mesh.h"

bool objloader_load_mesh(mesh* out, int file, size_t file_size);

bool objloader_load_mesh_from_path(mesh* out, const char* path);

#endif