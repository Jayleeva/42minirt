#include "../inc/minirt.h"

int	hit_sphere(const t_ray *r, const t_sp *s, float tmin, float tmax, t_hit *out)
{
	t_vector	oc;
	float		a, half_b, c, disc, sqrtd, t;

	oc = v_from_points(s->coord, r->o); // hipothemuse
	a = v_dot(r->d, r->d); // 
	half_b = v_dot(oc, r->d); // besoin de la moitie de l'hipothemuse? pourquoi?
	c = v_dot(oc, oc) - (s->diameter * 0.5f) * (s->diameter * 0.5f);
	disc = half_b * half_b - a * c;
	if (disc < 0.0f)
		return (0);
	sqrtd = sqrtf(disc);
	t = (-half_b - sqrtd) / a;
	if (t < tmin || t > tmax)
	{
		t = (-half_b + sqrtd) / a;
		if (t < tmin || t > tmax)
			return (0);
	}
	out->t = t;
	out->p = p_add_v(r->o, v_scale(r->d, t));
	out->n = v_norm(v_from_points(s->coord, out->p));
	if (v_dot(out->n, r->d) > 0.0f)
		out->n = v_scale(out->n, -1.0f);
	out->kind = SPHERE;
	return (1);
}
