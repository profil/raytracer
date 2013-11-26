#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "render.h"

#define WIDTH 6000
#define HEIGHT 1080



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
	struct ray current_ray;
	struct vector camera;
	int x, y;

	/* hard coded values for now.. */
	struct sphere spheres[] = {
		{{200, 300, 100}, 80, 0xffffff},
		{{500, 300, 100}, 80, 0xffffff},
		{{1400, 300, 100}, 50, 0xffffff},
		{{1200, 550, 300}, 150, 0xffffff},
		

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

	camera = makevec(WIDTH/2, HEIGHT/2, -400);
	
	for(x = 0; x < WIDTH; x++) {
		for(y = 0; y < HEIGHT; y++) {
			current_ray = makeray(camera, norm(sub(makevec(x, y, 100), camera)));

			pixels[WIDTH * y + x] = radiance(current_ray,
					spheres, sizeof(spheres)/sizeof(struct sphere),
					lights, sizeof(lights)/sizeof(struct sphere),
					0);
		}
	}

	write_image(pixels);

	return 0;
}
