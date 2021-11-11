#include <stdlib.h>
#include <stdio.h>

#include "float3.h"
#include "primitive.h"
#include "sphere.h"
#include "camera.h"

// random float between -1 and 1
static float randf() {
    return 2.0f * (((float)rand())/((float)(RAND_MAX)) - 0.5f);
}


int main() {
    // camera setup
    camera cam = {
        .position = VEC_ZERO,
        .forward = VEC_FORW,
        .right = VEC_RIGHT,
        .upward = VEC_UP
    };
    camera_set_fov(&cam, 60);

    // scene building
    const int scene_size = 200;
    primitive scene[scene_size];
    sphere spheres[scene_size];

    for (size_t i = 0; i < scene_size; i++) {
        sphere s = {
            .center = {2.0f * randf(), randf(), 4.0f + randf()},
            .radius = fabsf(randf() / 2)
        };
        spheres[i] = s;
        scene[i] = sphere_get_primitive(&spheres[i]);
        scene[i].color = color_rand();
    }


    // frame rendering
    const int width = 1920;
    const int height = 1080;
    color pixels[width * height];

    camera_render(&cam, pixels, width, height, scene, scene_size);

    FILE *fp = fopen("./first.ppm", "wb"); /* b - binary mode */
    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    fwrite(pixels, width * height, sizeof(color), fp);
    fclose(fp);

    return EXIT_SUCCESS;
}


