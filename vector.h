struct vector {
	/* coordinates */
	float x, y, z;
};

struct vector vec(float, float, float);
struct vector add(struct vector, struct vector);
struct vector sub(struct vector, struct vector);
struct vector scale(float, struct vector);
struct vector norm(struct vector a);
struct vector cross(struct vector a, struct vector b);
float dot(struct vector, struct vector);
