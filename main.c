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
	double fov, aspectratio;

	/* hard coded values for now.. */
	struct sphere spheres[] = {
		{{0, 0, 110000}, 100000, 0xffffff}, /* back */
		{{-105000, 0, 0}, 100000, 0xff0000}, /* left */
		{{105000, 0, 0}, 100000, 0x0000ff}, /* right */
		{{0, -105000, 0}, 100000, 0xffffff}, /* above */
		{{0, 105000, 0}, 100000, 0xffffff}, /* below */
		//{{0, 0, -110000}, 100000, 0x0000ff}, /* front */

		{{-20, 0, 20}, 10, 0x00ff00}, /* mirror */
		{{20, 7, 10}, 10, 0x00ff00}, /* glass */

	};
	struct sphere lights[] = {
		{{0, -55, 15}, 1, 0xff},
	};

	if((pixels = malloc(sizeof(unsigned int) * WIDTH*HEIGHT)) == NULL) {
		fprintf(stderr, "Could not allocate memory!\n");
		return 1;
	}

	camera = ray(vec(0, 0, -50), norm(vec(0, 0, 1)));
	camera_right = norm(cross(camera.d, vec(0, 1, 0)));
	camera_up = norm(cross(camera_right, camera.d));

	fov = tan(90/2.0 * (PI/180));
	aspectratio = (double)WIDTH / (double)HEIGHT;

	#pragma omp parallel for private(x) private(y) private(current_ray)
	for(x = 0; x < WIDTH; x++) {
		for(y = 0; y < HEIGHT; y++) {

			current_ray = ray(camera.p, norm(vec(
				(((double)x / (double)WIDTH) * 2.0 - 1.0) * fov * aspectratio,
				(((double)y / (double)HEIGHT) * 2.0 - 1.0) * fov,
				1)));

			/*
			use this instead?
			current_ray = ray(camera.p, add(
				add(scale(x / WIDTH - 0.5, camera_right),
					scale(y / HEIGHT - 0.5, camera_up)), camera.d));
			*/

			pixels[WIDTH * y + x] = radiance(current_ray,
					spheres, sizeof(spheres)/sizeof(struct sphere),
					lights, sizeof(lights)/sizeof(struct sphere),
					0);
		}
	}

	write_image(pixels);

	return 0;
}
