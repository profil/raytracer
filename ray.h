struct ray {
	/* position and direction */
	struct vector p;
	struct vector d;
};

struct ray ray(struct vector, struct vector);
