#include "../inc/minirt.h"

float	compute_sp_discr(const t_ray *r, t_sp *s)
{
	float	rads;
	float	discr;

	rads = s->diameter * 0.5f;
	s->x = v_sub(r->o, s->coord);
	s->a = v_dot(r->d, r->d);
	s->half_b = v_dot(s->x, r->d);
	s->c = v_dot(s->x, s->x) - rads * rads;
	discr = s->half_b * s->half_b - s->a * s->c;
	return (discr);
}

// Vérifie si un rayon (r) intersecte une sphère (s).
// Si oui, stocke les infos d’intersection dans out
// Retourne 1 si hit, 0 sinon.
int	hit_sphere(const t_ray *r, t_sp *s, float tmax, t_hit *out)
{
	float		discr;
	float		t;

	discr = compute_sp_discr(r, s);
	if (discr < 0.0f)
		return (0);
	t = (-s->half_b - sqrtf(discr)) / s->a;
	if (t < EPS || t > tmax)
	{
		t = (-s->half_b + sqrtf(discr)) / s->a;
		if (t < EPS || t > tmax)
			return (0);
	}
	out->t = t;
	out->p = v_add(r->o, v_scale(r->d, t));
	out->n = v_norm(v_sub(out->p, s->coord));
	if (v_dot(out->n, r->d) > 0.0f)
		out->n = v_scale(out->n, -1.0f);
	out->kind = SPHERE;
	return (1);
}
