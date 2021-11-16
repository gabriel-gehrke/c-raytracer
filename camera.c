#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "raycaster.h"
#include "util.h"




static color raycast_scene(const camera* cam, float frustX, float frustY, const primitive* scene, size_t scene_size) {

    ray ray =
    {
        .origin = cam->position,
        .direction = vmac(vmac(vmul(cam->forward, cam->focus), cam->upward, frustY), cam->right, frustX)
    };

    // cast ray with 5 bounces
    return raycaster_cast_ray(&ray, scene, scene_size, 2);
}

static void print_percent(float percent) {
    printf("\r%.2f %%", (double) percent * 100.0f);
    fflush(stdout);
}

void camera_set_fov(camera* cam, float fov) {
    const float extent = 2.0f; // -1 to 1
    cam->fov = fov;
    cam->focus = (extent * 0.5f) / tanf(fov * 0.5f * (PI / 180.0f));
}

void camera_render(const camera* cam, color* pixels, int width, int height, const primitive* scene, size_t scene_size) {

    // Calculate the aspect ration
    float fwidth = width;
    float fheight = height;

    float hwidth = fwidth / 2.0f;
    float hheight = fheight / 2.0f;

    float width_scale = width < height ? fwidth / fheight : 1.0;
    float height_scale = height < width? fheight / fwidth : 1.0;

    // Create the image by casting one ray into the scene for each pixel
    for (int y = 0; y < height; y++) {
        int row_offs = y * width;

        for (int x = 0; x < width; x++) {

            float frustX = ((x - hwidth) / hwidth) * width_scale;
            float frustY = ((hheight - y) / hheight) * height_scale; 

            pixels[row_offs + x] = raycast_scene(cam, frustX, frustY, scene, scene_size);
        }

        print_percent((float) (y+1) / (float) height);
        
    }
    puts("\ndone.\n");
}

