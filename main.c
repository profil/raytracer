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


	/*int running, x, y, z, i, j, cSphere, shadow, level;
	float lam, r, g, b, coef, t, t1, t2, n_cof;
	struct point d, hit;
	struct ray R, n, L;*/

	/* hard coded values for now.. */
	struct sphere spheres[] = {
		{{100, 100, 100}, 40, 0x00f4005f}
		/*
		{{-1e5 - 49, 0, 0}, 1e5, 0x00bd3f3f},
		{{1e5 + 49, 0, 0}, 1e5, 0x003f3fbd},
		{{0, 0, -1e5 - 81.6}, 1e5, 0x00bdbdbd},
		{{0, 0, 1e5 + 88.4}, 1e5, 0x00000000},
		{{0, -1e5 - 40.8, 0}, 1e5, 0x00bdbdbd},
		{{0, 1e5 - 40.8, 0}, 1e5, 0x00bdbdbd},
		{{-23, -24.3, -34.5}, 16.5, 0x00efefef},
		{{23, -24.3, -3.6}, 16.5, 0x00efefef},
		*/
	};
	/*struct sphere lights[] = {
		{{0, 24.3, 0}, 1.5, 0x00aaaaaa},
	};
*/


	for(x = 0; x < WIDTH; x++) {
		for(y = 0; y < HEIGHT; y++) {
			current_ray = makeray(makevec(x, y, z), makevec(0, 0, 1));

			pixels[WIDTH * y + x] = radiance(current_ray, spheres, sizeof(spheres)/sizeof(struct sphere), 0);



/*





			R.s = mkp(x, y, z);
			R.e = mkp(0, 0, 1);
			r = g = b = 0x00;
			coef = 1.0f;
			level = 0;

			do {
				t = 5000.0f;
				cSphere = -1;
				for(i = 0; i < NSPHERES; i++) {
					if(sphere_collision(R, spheres[i], &t)) {
						cSphere = i;
					}
				}
				if(cSphere == -1) 
					break;

				hit = mkp(x, y, t);
				n.s = sub(hit, spheres[cSphere].p);
				n_cof = dot(n.s, n.s);
				if(n_cof == 0)
					break;
				n.s.x /= sqrtf(n_cof);
				n.s.y /= sqrtf(n_cof);
				n.s.z /= sqrtf(n_cof);

				for(i = 0; i < NLIGHTS; i++) {
					d = sub(lights[i].p, hit);
					if(dot(n.s, d) <= 0.0f)
						continue;

					t1 = sqrtf(dot(d, d));
					if(t1 <= 0.0f)
						continue;

					L.s = hit;
					L.e = mkp(d.x/t1, d.y/t1, d.z/t1);

					shadow = 0;
					t = 5000.0f;
					for(j = 0; j < NSPHERES; j++) {
						if(sphere_collision(L, spheres[i], &t)) {
							shadow = 1;
							break;
						}
					}
					if(!shadow) {
						lam = dot(n.s, L.e) * coef;
						r += lam * lights[i].r;
						g += lam * lights[i].g;
						b += lam * lights[i].b;
					}
				}
				coef *= 0.1;
				R.s = hit;
				R.e.x -= 2.0f * dot(R.e, n.s) * n.s.x;
				R.e.y -= 2.0f * dot(R.e, n.s) * n.s.y;
				R.e.z -= 2.0f * dot(R.e, n.s) * n.s.z;
				level++;
			}
			while((coef > 0.0f) && (level < 10));

		*/}
	}

	write_image(pixels);

	return 0;
}
