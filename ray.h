struct ray {
	/* position and direction */
	struct vector p;
	struct vector d;
};

struct ray makeray(struct vector, struct vector);
