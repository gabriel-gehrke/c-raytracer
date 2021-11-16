#include <stdlib.h>
#include <stdio.h>

#include "float3.h"
#include "primitive.h"
#include "sphere.h"
#include "camera.h"

#define WIDTH 1280
#define HEIGHT 720
#define TOTAL_PIXELS (WIDTH * HEIGHT)
color pixels[TOTAL_PIXELS];

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

    camera_render(&cam, pixels, WIDTH, HEIGHT, scene, scene_size);

    FILE *fp = fopen("./first.ppm", "wb"); /* b - binary mode */
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    fwrite(pixels, TOTAL_PIXELS, sizeof(color), fp);
    fclose(fp);

    return EXIT_SUCCESS;
}


