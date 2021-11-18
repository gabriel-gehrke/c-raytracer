#include <stdlib.h>
#include <stdio.h>

#include "float3.h"
#include "primitive.h"
#include "sphere.h"
#include "camera.h"
#include "objloader.h"

#define WIDTH 3840
#define HEIGHT 2160
#define TOTAL_PIXELS (WIDTH * HEIGHT)
color pixels[TOTAL_PIXELS];


int main() {

    mesh icosphere;
    return objloader_load_mesh_from_path(&icosphere, "./icosphere.obj");

    /*
    // camera setup
    camera cam = {
        .position = VEC_ZERO,
        .forward = VEC_FORW,
        .right = VEC_RIGHT,
        .upward = VEC_UP
    };
    camera_set_fov(&cam, 60);

    // scene building
    const size_t scene_size = 100;
    primitive scene[scene_size];
    sphere spheres[scene_size];

    for (size_t i = 0; i < scene_size; i++) {

        gen_sphere: ; // goto madness requires an empty statement after label

        sphere s = {
            .center = {2.0f * randf(), randf(), 4.0f + randf()},
            .radius = fabsf(randf() / 2)
        };
        // prevent collision
        for (size_t j = 0; j < i; j++) {
            sphere* o = spheres + j;
            float r = s.radius + o->radius;
            if (vdist(s.center, o->center) < r) {
                goto gen_sphere;
            }
        }

        spheres[i] = s;
        scene[i] = sphere_get_primitive(&spheres[i]);
        scene[i].color = color_rand();
    }

    camera_render(&cam, pixels, WIDTH, HEIGHT, scene, scene_size);

    FILE *fp = fopen("./first.ppm", "wb");
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    fwrite(pixels, TOTAL_PIXELS, sizeof(color), fp);
    fflush(fp);
    fclose(fp);
    */
    

    return EXIT_SUCCESS;
}


