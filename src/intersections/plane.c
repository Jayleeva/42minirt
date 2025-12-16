#include "../inc/minirt.h"

int	hit_plane(const t_ray *r, const t_pl *pl, float tmax, t_hit *out)
{
	float 		denom;
	float 		t;
	t_vector 	p;
	t_vector	n;

	// Si D·n ≈ 0 : rayon // au plan -> pas d'intersection stabl
	n = v_norm(pl->ornt);
	denom = v_dot(r->d, n);
	if (fabsf(denom) < 1e-6f)
	{
		//printf("denom too small\n");
		return (0);
	}

	// t = ((center - O)·n) / (D·n)
	t = v_dot(v_sub(pl->coord, r->o), n) / denom;
	if (t < EPS || t > tmax) //essayer en gardant un seul des deux
	{
		//printf("try commenting the return\n");
		return (0);
	}

	p = v_add(r->o, v_scale(r->d, t));

	out->t    = t;
	out->p    = p;
	out->n    = n; // déjà unitaire (utiliser V ou -V)
	if (v_dot(out->n, r->d) > 0.0f)
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