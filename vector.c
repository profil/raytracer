#include <math.h>
#include "vector.h"

struct vector vec(float x, float y, float z) {
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
struct vector scale(float i, struct vector a) {
	struct vector c;
	c.x = a.x * i;
	c.y = a.y * i;
	c.z = a.z * i;
	return c;
}
struct vector norm(struct vector a) {
	return scale(1.0f / sqrt(dot(a, a)), a);
}
struct vector cross(struct vector a, struct vector b) {
	struct vector c;
	c.x = a.y*b.z - a.z*b.y;
	c.y = a.z*b.x - a.x*b.z;
	c.z = a.x*b.y - a.y*b.x;
	return c;
}
float dot(struct vector a, struct vector b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
