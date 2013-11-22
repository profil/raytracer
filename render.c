#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "render.h"


unsigned int radiance(struct ray current_ray, struct sphere *spheres, int spheres_len, int depth) {
	double distance;
	int sphere_id;
	unsigned int color = 0;
	struct sphere current_sphere;
	struct vector hit, normal;


	for(;;) {
		if((distance = sphere_intersect(current_ray, spheres, spheres_len, &sphere_id)) == 0 || depth > 5) { 
			color = 0x00; /* return background color, black */
			break;
		}

		current_sphere = spheres[sphere_id];
		hit = makevec(current_ray.p.x, current_ray.p.y, distance);
		normal = norm(sub(hit, current_sphere.c));

		/* vector glass_normal = dot(norm, current_ray.d) < 0 ? normal : scale(-1, normal); */
		color += current_sphere.color;


		/* only one type of material so far */

		/* take care of lights and shadows */

		current_ray.d = normal;
		depth++;
	}
	return color;
}
