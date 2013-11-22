struct sphere {
	/* center and radius */
	struct vector c;
	double r;
	unsigned int color; /* 0xXXRRGGBB */
};


double sphere_collision(struct ray, struct sphere);
int sphere_intersect(struct ray, struct sphere *, int, int *);

