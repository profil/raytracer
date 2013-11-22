#include <math.h>
#include "vector.h"
#include "ray.h"
#include "sphere.h"

/* see http://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Example
 *
 * returns the z coordinate for the reflecting/refracting rays
 * or zero if no collision occured
 */
double sphere_collision(struct ray r, struct sphere s) {
	double discriminant, D, t1, t2, vd;
	struct vector v;

	v = sub(r.p, s.c);
	vd = dot(v, r.d);
	/* discriminant = (v·d)² - (v²+r²) */
	discriminant = vd * vd - dot(v, v) + s.r * s.r;

	if(discriminant < 0.0f)
		/* no intersection */
		return 0;
	
	D = sqrt(discriminant);
	t1 = vd + D;
	t2 = vd - D;

	if(t1 > 0.0f && t1 < t2) {
		return t1;
	}
	else if(t2 > 0.0f) {
		return t2;
	}
	else {
		return 0;
	}
}


int sphere_intersect(struct ray r, struct sphere *spheres, int spheres_len, int *sphere_id) {
	int i;
	double t = 0, d = 0;
	for(i = 0; i < spheres_len; i++) {
		if((d = sphere_collision(r, spheres[i])) != 0) {
			if(t < d) {
				d = t;
				*sphere_id = i;
			}
		}
	}
	return d;
}


