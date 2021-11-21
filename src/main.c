#include <stdlib.h>
#include <stdio.h>

#include "primitive.h"
#include "sphere.h"
#include "camera.h"
#include "util.h"
#include "objloader.h"

#define WIDTH 1920
#define HEIGHT 1080
#define TOTAL_PIXELS (WIDTH * HEIGHT)
color pixels[TOTAL_PIXELS];

static void render_spheres() {
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
    primitive scene[scene_size + 1];
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
}

static void render_mesh(mesh m) {
    

    camera cam = {
        .position = {.x = 0, .y = 0, .z = -5},
        .forward = VEC_FORW,
        .right = VEC_RIGHT,
        .upward = VEC_UP
    };
    camera_set_fov(&cam, 60);

    // scene
    primitive scene[3];

    sphere s1 = {{0, -1, -1}, 0.3f};
    scene[0] = sphere_get_primitive(&s1);
    scene[0].color = color_rand();

    sphere s2 = {{-0.2f, 0, -4}, 0.2f};
    scene[1] = sphere_get_primitive(&s2);
    scene[1].color = color_rand();

    scene[2] = mesh_get_primitive(&m);
    scene[2].color = color_rand();

    camera_render(&cam, pixels, WIDTH, HEIGHT, scene, 3);
}


int main() {
    mesh icosphere;
    objloader_load_mesh_from_path(&icosphere, "./icosphere.obj");
    render_mesh(icosphere);
    

    FILE *fp = fopen("./first.ppm", "wb");
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    fwrite(pixels, TOTAL_PIXELS, sizeof(color), fp);
    fflush(fp);
    fclose(fp);

    return EXIT_SUCCESS;
}


