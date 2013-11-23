struct sphere {
	/* center and radius */
	struct vector c;
	float r;
	unsigned int color; /* 0xXXRRGGBB */
};


float sphere_collision(struct ray, struct sphere);
int sphere_intersect(struct ray, struct sphere *, int, int *);

