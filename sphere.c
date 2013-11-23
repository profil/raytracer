#include <math.h>
#include "vector.h"
#include "ray.h"
#include "sphere.h"

/* see http://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Example
 *
 * returns the z coordinate for the reflecting/refracting rays
 * or zero if no collision occured
 */
double sphere_collision(struct ray ray, struct sphere sphere) {
	double discriminant, D, t1, t2, vd;
	struct vector v;

	v = sub(sphere.c, ray.p);
	vd = dot(v, ray.d);
	/* discriminant = (v·d)² - (v²+r²) */
	discriminant = vd * vd - dot(v, v) + sphere.r * sphere.r;

	if(discriminant < 0.0f)
		/* no intersection */
		return 0;
	
	D = sqrt(discriminant);
	t1 = vd + D;
	t2 = vd - D;

	if(t1 <= t2) {
		if(t1 > 0.0f) {
			return t1;
		}
		else {
			return 0;
		}
	}
	else {
		if(t2 > 0.0f) {
			return t2;
		}
		else {
			return 0;
		}
	}
}


int sphere_intersect(struct ray r, struct sphere *spheres, int spheres_len, int *sphere_id) {
	int i;
	double t = 1e100, distance = 0;
	for(i = 0; i < spheres_len; i++) {
		distance = sphere_collision(r, spheres[i]);
		if(distance > 0.0f) {
			if(distance < t) {
				t = distance;
				*sphere_id = i;
			}
		}
	}
	return t != 1e100 ? t : 0;
}


