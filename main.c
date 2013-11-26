#include <stdio.h>
#include <math.h>

#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "render.h"

#define WIDTH 800
#define HEIGHT 600



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
	unsigned int pixels[WIDTH*HEIGHT] = {0};
	struct ray current_ray;
	int x, y;

	/* hard coded values for now.. */
	struct sphere spheres[] = {
		{{200, 300, 100}, 80, 0xb20000},
	};
	struct sphere lights[] = {
		{{400, 0, 100}, 1, 0xff},
		{{400, 600, 100}, 1, 0xff},
		{{0, 0, 100}, 1, 0xff},
		{{0, 600, 100}, 1, 0xff},
	};


	/* TODO:
	 * Use a camera to get the correct perspective.
	 */
	for(x = 0; x < WIDTH; x++) {
		for(y = 0; y < HEIGHT; y++) {
			current_ray = makeray(makevec(400, 300, 0), norm(makevec(x-400, y-300, 10)));

			pixels[WIDTH * y + x] = radiance(current_ray,
					spheres, sizeof(spheres)/sizeof(struct sphere),
					lights, sizeof(lights)/sizeof(struct sphere),
					0);
		}
	}

	write_image(pixels);

	return 0;
}
