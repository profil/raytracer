struct vector {
	/* coordinates */
	double x, y, z;
};

struct vector makevec(double, double, double);
struct vector add(struct vector, struct vector);
struct vector sub(struct vector, struct vector);
struct vector scale(double, struct vector);
struct vector norm(struct vector a);
double dot(struct vector, struct vector);
