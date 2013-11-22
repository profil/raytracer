#include "vector.h"

vector makevec(float x, float y, float z) {
	vector c;
	c.x = x;
	c.y = y;
	c.z = z;
	return c;
}
vector add(vector a, vector b) {
	vector c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}
vector sub(vector a, vector b) {
	vector c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}
vector scale(float i, vector a) {
	vector c;
	c.x = a.x * i;
	c.y = a.y * i;
	c.z = a.z * i;
	return c;
}
float dot(vector a, vector b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
