#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "render.h"

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265358979323846


void write_image(unsigned int *pixels) { 
	int i;
	FILE *fp = fopen("image.ppm", "w");

	fprintf(fp, "P3\n%d %d\n%d\n", WIDTH, HEIGHT, 255);
	
	for(i = 0; i < WIDTH*HEIGHT; i++) {
		fprintf(fp, "%u %u %u\n", (unsigned char)(pixels[i] >> 16),
			(unsigned char)(pixels[i] >> 8),
			(unsigned char)pixels[i]);
	}
	fclose(fp);
}

int main(int argc, char *argv[]) {
	unsigned int *pixels;
	struct ray current_ray, camera;
	struct vector camera_up, camera_right;
	int x, y;
	double fov, fovx, fovy;

	/* hard coded values for now.. */
	struct sphere spheres[] = {
		{{200, 300, 100}, 80, 0x0000ff},
		{{500, 300, 100}, 80, 0xff0000},
		{{1400, 300, 100}, 50, 0x00ff00},
		{{1200, 550, 300}, 150, 0xf0000f},
		

		{{400, 109000, 100}, 100000, 0xffffff},
		{{400, 300, 109000}, 100000, 0xffffff},
	};
	struct sphere lights[] = {
		{{400, 50, -10}, 1, 0xff},
	};

	if((pixels = malloc(sizeof(unsigned int) * WIDTH*HEIGHT)) == NULL) {
		fprintf(stderr, "Could not allocate memory!\n");
		return 1;
	}

	camera = makeray(makevec(0, 0, 0), norm(makevec(0, 0, -1)));
	camera_right = norm(cross(camera.d, makevec(0, 1, 0)));
	camera_up = norm(cross(camera_right, camera.d));

	fov = 130/2.0 * (PI/180);
	fovx = tan(fov);
	fovy = tan((double)HEIGHT/(double)WIDTH * fov);

	#pragma omp parallel for private(x) private(y) private(current_ray)
	for(x = 0; x < WIDTH; x++) {
		for(y = 0; y < HEIGHT; y++) {

			current_ray = makeray(camera.p, norm(makevec((x - WIDTH/2) * fovx, (y - HEIGHT/2) * fovy, 50)));

			pixels[WIDTH * y + x] = radiance(current_ray,
					spheres, sizeof(spheres)/sizeof(struct sphere),
					lights, sizeof(lights)/sizeof(struct sphere),
					0);
		}
	}

	write_image(pixels);

	return 0;
}
