#include "../inc/minirt.h"

int	hit_plane(const t_ray *r, const t_pl *pl, float tmin, float tmax, t_hit *out)
{
	float	t;

	if (r->d.o_y < EPS)
		return (0); // pas d'intersection car paralleles ou coplanaire

	t = (r->o.y * -1) / r->d.o_y;

	/*Scenario: A ray intersecting a plane from above
	Given p ← plane()
	And r ← ray(point(0, 1, 0), vector(0, -1, 0))
	When xs ← local_intersect(p, r)
	Then xs.count = 1
	And xs[0].t = 1
	And xs[0].object = p
	Scenario: A ray intersecting a plane from below
	Given p ← plane()
	And r ← ray(point(0, -1, 0), vector(0, 1, 0))
	When xs ← local_intersect(p, r)
	Then xs.count = 1
	And xs[0].t = 1
	And xs[0].object = p*/

	(void)tmin;
	(void)tmax;
	/*if (t < tmin || t > tmax)
		return (0);*/ // n'est pas dans les bornes (besoin?)
		
	out->t = t;
	out->p = p_add_v(r->o, v_scale(r->d, t));
	out->n = v_norm(v_from_points(pl->coord, out->p)); // manque prise en compte de l'orientation?
	if (v_dot(out->n, r->d) > 0.0f) // si normale inversee, reinverser
		out->n = v_scale(out->n, -1.0f);
	out->kind = PLANE;
	return (1);
}

/*The logic to intersect a ray with a plane is the only other bit that needs
implementing, and it has four cases to consider:
1. The ray is parallel to the plane, and will thus never intersect it.
2. The ray is coplanar with the plane, which is to say that the ray’s origin is
on the plane, and the ray’s direction is parallel to the plane. You’re viewing
the plane edge-on. In this case, every point on the ray intersects the plane,
resulting in an infinite number of intersections. That’s unwieldy! But
since a plane is infinitely thin, it’s invisible when viewed like this, so we’ll
assume the ray misses in this case.
3. The ray origin is above the plane.
4. The ray origin is below the plane.


implement the following formula for computing the intersection of a ray with a plane.
Note that this formula only works if the plane is as described above—in xz, with the normal pointing in the positive y direction.

t = −origin y
____________
direction y

The variable origin is the ray’s origin, and direction is the ray’s direction vector.
The following pseudocode shows how the complete local_intersect() function might look.

function local_intersect(ray, plane)
	if abs(ray.direction.y) < EPSILON
		return () # empty set -- no intersections
	t ← -ray.origin.y / ray.direction.y
	return ( intersection(t, plane) )*/