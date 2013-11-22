#include <math.h>
#include "vector.h"

struct vector makevec(double x, double y, double z) {
	struct vector c;
	c.x = x;
	c.y = y;
	c.z = z;
	return c;
}
struct vector add(struct vector a, struct vector b) {
	struct vector c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}
struct vector sub(struct vector a, struct vector b) {
	struct vector c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}
struct vector scale(double i, struct vector a) {
	struct vector c;
	c.x = a.x * i;
	c.y = a.y * i;
	c.z = a.z * i;
	return c;
}
struct vector norm(struct vector a) {
	struct vector c;
	double cof = 1 / sqrt(dot(a, a));
	c.x *= cof;
	c.y *= cof;
	c.z *= cof;
	return c;
}
double dot(struct vector a, struct vector b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
