#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "objloader.h"

static bool parse_vertex(float3* out, char* c) {
    char* s = strtok(c, " ");
    int i = 0;

    float* fptr = (float*) out;

    // parse every coordinate of vert and write to out
    for (; s != NULL && i < 3; i++) {
        *fptr++ = (float) atof(s);
        s = strtok(NULL, " ");
    }

    return i == 3;
}

bool objloader_load_mesh(mesh* out, int file, size_t file_size) {

    // create a read-only memory mapping of the provided file
    char* head = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, file, 0);

    mesh m = {0};
    size_t line_num = 1;

    // go through file, line by line
    while (file_size > 3) {
        // calc line len
        size_t line_len = (size_t) (memchr(head, '\n', file_size) - (void*)head);
        if (line_len > file_size) return false;

        // create buffer for line, copy line into buffer, append 0
        char line[line_len + 1];
        line[line_len] = 0;
        strncpy(line, head, line_len);

        printf("at line %lu: %s\n", line_num, line);

        if (strncmp(line, "v ", 2) == 0) {
            // a vertex definition: parse vertex
            printf("Found a vertex definition in line %lu: \"%s\"\n", line_num, line);
            float3 vert;
            if (!parse_vertex(&vert, line + 2)) return false;
            vprint(vert, stdout);

        } else if (strncmp(line, "vn ", 3)) {
            // a normal definition
        } else if (strncmp(line, "f ", 2)) {
            // defines
        }


        // reduce amount of remaining bytes
        file_size -= line_len + 1;
        head += line_len + 1;
        line_num++;
    }

    *out = m;
    return true;
}

bool objloader_load_mesh_from_path(mesh* out, const char* path) {
    // try to open file
    int file = open(path, O_RDONLY);
    if (file == -1) return false;

    bool success = false;

    // get file size and load mesh
    struct stat filestat;
    if (fstat(file, &filestat) == 0) {
        size_t size = (size_t)filestat.st_size;
        success = objloader_load_mesh(out, file, size);
    }

    // finally close file
    close(file);
    return success;
}
