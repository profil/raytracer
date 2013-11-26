#include "vector.h"
#include "ray.h"

struct ray makeray(struct vector p, struct vector d) {
	struct ray r;
	r.p = p;
	r.d = d;
	return r;
}
