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
	int x, y, z = 0;

	/* hard coded values for now.. */
	struct sphere spheres[] = {
		{{100, 100, 100}, 80, 0xff0000},
		{{400, 100, 100}, 80, 0x00ff00},
	};
	struct sphere lights[] = {
		{{0, 100, 15}, 6, 0xff},
	};


	/* TODO:
	 * Use a camera to get the correct perspective.
	 */
	for(x = 0; x < WIDTH; x++) {
		for(y = 0; y < HEIGHT; y++) {
			current_ray = makeray(makevec(x, y, z), makevec(0, 0, 1));

			pixels[WIDTH * y + x] = radiance(current_ray,
					spheres, sizeof(spheres)/sizeof(struct sphere),
					lights, sizeof(lights)/sizeof(struct sphere),
					0);
		}
	}

	write_image(pixels);

	return 0;
}
