#include <stdio.h>

#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "render.h"

unsigned char clamp(int input) {
	if(input > 0xff) {
		return 0xff;
	}
	else {
		return (unsigned char)input;
	}
}

unsigned int radiance(struct ray current_ray, struct sphere *spheres, int spheres_len, struct sphere *lights, int lights_len, int depth) {
	float distance, lambert;
	int sphere_id, i;
	unsigned int color = 0;
	unsigned char r, g, b;
	struct sphere current_sphere;
	struct vector hit, normal;
	struct ray shadow;

	for(;;) {
		if((distance = sphere_intersect(current_ray, spheres, spheres_len, &sphere_id)) == 0 || depth > 5) { 
			color += 0x00; /* return background color, black */
			break;
		}
		current_sphere = spheres[sphere_id];
		hit = makevec(current_ray.p.x, current_ray.p.y, distance);
		normal = norm(sub(hit, current_sphere.c));

		/* only one type of material so far */
		/* struct vector glass_normal = dot(norm, current_ray.d) < 0 ? normal : scale(-1, normal); */


		/* take care of lights and shadows */
		for(i = 0; i < lights_len; i++) {
			shadow.d = norm(sub(lights[i].c, hit));
			shadow.p = hit;
		
			
			/* if not in shadow, give color */
			if(!sphere_intersect(shadow, spheres, spheres_len, &sphere_id)) {
				lambert = dot(shadow.d, normal);

				r = current_sphere.color >> 16 & 0xff;
				g = current_sphere.color >> 8 & 0xff;
				b = current_sphere.color & 0xff;

				r += lights[i].color * lambert;
				g += lights[i].color * lambert;
				b += lights[i].color * lambert;
				color = r << 16 | g << 8 | b;
			}
		}

		/* The reflected ray */
		current_ray.p = hit;
		current_ray.d = sub(current_ray.d, scale(2.0f * dot(normal, current_ray.d), normal));
		depth++;
	}
	return color;
}
