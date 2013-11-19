#include "vector.h"

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
vector mult(vector a, vector b) {
	vector c;
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return c;
}
vector cross(vector a, vector b) {
	vector c;
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return c;
}
float dot(vector a, vector b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
