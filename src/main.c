/* made by profil <profil@errno.se> 2013 */
#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>

#include "vector.h"

#define WIDTH 800
#define HEIGHT 600
#define BPP 32



/* algorithm taken from
	http://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Example
*/
int sphere_collision(struct ray r, struct sphere s, float *t) {
	float D, t0, t1;
	int ret;
	struct point v;

	v = sub(s.p, r.s);
	D = dot(v,r.e) * dot(v,r.e) - dot(v,v) + s.r * s.r;
	if(D < 0.0f) return 0;

	ret = 0;

	t0 = dot(v,r.e) - sqrtf(D);
	t1 = dot(v,r.e) + sqrtf(D);
	if(t0 > 0.1f && t0 < *t) {
		*t = t0;
		ret = 1;
	}
	if(t1 > 0.1f && t1 < *t) {
		*t = t1;
		ret = 1;
	}
	return ret;
}

void setpixel(SDL_Surface *sur, int x, int y, Uint32 pixel) {
	Uint32 *pixels = (Uint32 *)sur->pixels;
	pixels[(sur->w * y) + x] = pixel;
}

int main(int argc, char *argv[]) {
	int running, x, y, z, i, j, cSphere, shadow, level;
	float lam, r, g, b, coef, t, t1, t2, n_cof;
	SDL_Surface* scr;
	SDL_Event ev;
	struct point d, hit;
	struct ray R, n, L;
	struct sphere spheres[NSPHERES] = {
		{{0, 0, 500}, 80},
		{{400, 0, 500}, 80},
		{{800, 0, 500}, 80},
		{{0, 200, 500}, 80},
		{{400, 200, 500}, 80},
		{{800, 200, 500}, 80},
		{{0, 400, 500}, 80},
		{{400, 400, 500}, 80},
		{{800, 400, 500}, 80}};
	struct light lights[NLIGHTS] = {
		{{0, 0, 100}, 0xff, 0xff, 0xff},
		{{400, 0, 100}, 0xff, 0xff, 0xff},
		{{800, 0, 100}, 0xff, 0xff, 0xff},
		{{0, 200, 100}, 0xff, 0xff, 0xff},
		{{400, 200, 100}, 0xff, 0xff, 0xff},
		{{800, 200, 100}, 0xff, 0xff, 0xff},
		{{0, 400, 100}, 0xff, 0xff, 0xff},
		{{400, 400, 100}, 0xff, 0xff, 0xff},
		{{800, 400, 100}, 0xff, 0xff, 0xff}};

	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "Error initializing SDL.\n");
		return 1;
	}
	scr = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
	if(scr == NULL) {
		fprintf(stderr, "Error setting video mode.\n");
		return 1;
	}

	running = 1;
	z = 0;
	while(running) {
		while(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT)
				running = 0;
			if(ev.type == SDL_KEYDOWN) {
				switch(ev.key.keysym.sym) {
					case SDLK_UP:
						spheres[0].p.y -= 10;
						break;
					case SDLK_DOWN:
						spheres[0].p.y += 10;
						break;
					case SDLK_LEFT:
						spheres[0].p.x -= 10;
						break;
					case SDLK_RIGHT:
						spheres[0].p.x += 10;
						break;
					case SDLK_a:
						spheres[0].p.z -= 10;
						break;
					case SDLK_z:
						spheres[0].p.z += 10;
						break;
					case SDLK_o:
						spheres[0].r += 10;
						break;
					case SDLK_p:
						spheres[0].r -= 10;
						break;
					case SDLK_ESCAPE:
						running = 0;
						break;
					default:
						break;
				}
			}
		}
		for(x = 0; x < WIDTH; x++) {
			for(y = 0; y < HEIGHT; y++) {
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

				setpixel(scr, x, y, SDL_MapRGB(scr->format,
						(unsigned char)(r),
						(unsigned char)(g),
						(unsigned char)(b)));
			}
		}
		SDL_Flip(scr);
		SDL_Delay(50);
	}

	SDL_Quit();
	return 0;
}
