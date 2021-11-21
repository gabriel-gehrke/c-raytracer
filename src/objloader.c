#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "objloader.h"
#include "util.h"
#include "assert.h"

static bool parse_float3(float3* out, char* c) {
    // split string by spaces
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

static bool parse_triangle(triangle* out, const char* c, const float3* verts, size_t verts_count, const float3* normals, size_t normals_count) {
    size_t v0_index, v1_index, v2_index, normal_index;
    volatile size_t dc; // don't care

    // read naively
    sscanf(c, "f %zu/%zu/%zu %zu/%zu/%zu %zu/%zu/%zu", 
        &v0_index, &dc, &normal_index,
        &v1_index, &dc, &dc,
        &v2_index, &dc, &dc
    );

    // indeces start at one
    assert(v0_index <= verts_count);
    assert(v1_index <= verts_count);
    assert(v2_index <= verts_count);
    assert(normal_index <= normals_count);

    out->v0 = verts[v0_index - 1];
    vprint(out->v0, stdout);
    out->v1 = verts[v1_index - 1];
    vprint(out->v1, stdout);
    out->v2 = verts[v2_index - 1];
    vprint(out->v2, stdout);
    out->normal = normals[normal_index - 1];
    vprint(out->normal, stdout);

    return true;
}

bool objloader_load_mesh(mesh* out, int file, size_t file_size) {

    // create a read-only memory mapping of the provided file
    const char* head = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, file, 0);

    // count number of verts/normals/triangles ahead of time and allocate space on stack
    const size_t verts_total = strncountstr(head, "\nv ", file_size);
    size_t verts_count = 0;
    float3 verts[verts_total];
    const size_t norms_total = strncountstr(head, "\nvn ", file_size);
    size_t norms_count = 0;
    float3 normals[norms_total];
    const size_t tris_total = strncountstr(head, "\nf ", file_size);
    size_t tris_count = 0;
    triangle triangles[tris_total];

    printf("Vertices: %zu\tNormals: %zu\tTriangles: %zu\n", verts_total, norms_total, tris_total);

    // keep track of the current line in file
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

        printf("at line %zu: %s\n", line_num, line);

        if (strncmp(line, "v ", 2) == 0) {
            // a vertex definition: parse vertex
            //printf("Found a vertex definition in line %zu: \"%s\"\n", line_num, line);
            float3 vert;
            if (!parse_float3(&vert, line + 2)) return false;
            vprint(vert, stdout);
            verts[verts_count++] = vert;

        } else if (strncmp(line, "vn ", 3) == 0) {
            // a normal definition: parse normal
            float3 normal;
            if (!parse_float3(&normal, line + 3)) return false;
            vprint(normal, stdout);
            normals[norms_count++] = normalized(normal);

        } else if (strncmp(line, "f ", 2) == 0) {
            // defines a triangle
            triangle tri;
            if (!parse_triangle(&tri, line, verts, verts_count, normals, norms_count)) return false;
            triangles[tris_count++] = tri;
        }


        // reduce amount of remaining bytes
        file_size -= line_len + 1;
        head += line_len + 1;
        line_num++;
    }

    // everyting got parsed!
    // -> allocate persistent data and copy triangles

    size_t triangle_bytes = tris_count * sizeof(triangle);

    out->tris_len = tris_count;
    out->tris = (triangle*) malloc(triangle_bytes);
    memcpy(out->tris, triangles, triangle_bytes);

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
