#include "../inc/minirt.h"

static t_vector	transform_n(const t_cy *cy, t_vector p, const t_ray *r)
{
	t_vector	n;
	t_vector	tmp1;
	t_vector	tmp2;

	tmp1 = v_sub(p, cy->coord);
	tmp2 = v_scale(v_norm(cy->ornt), cy->m);
	n = v_norm(v_sub(tmp1, tmp2));
	if (v_dot(n, r->d) > 0.0f)
		n = v_scale(n, -1.0f);
	return (n);
}

static void	assign_hitpoint(float t, t_vector p, t_vector n, t_hit *out)
{
	out->t = t;
	out->p = p;
	out->n = n;
	out->kind = CYLINDER;
}

float	find_t(const t_ray *r, t_cy *cy, int sign)
{
	float	t;
	float	rads;
	float	discr;

	rads = cy->diameter * 0.5f;
	t = -1;
	// Quadratique sur le flanc : a t^2 + 2*half_b t + c = 0
	cy->a = v_dot(r->d, r->d) - (cy->dv * cy->dv);						// a	= D|D - (D|V)^2
	cy->half_b = v_dot(r->d, cy->X) - (cy->dv * cy->xv);				// b/2	= D|X - (D|V)*(X|V) 
	cy->c = v_dot(cy->X, cy->X) - (cy->xv * cy->xv) - (rads * rads);	// c	= X|X - (X|V)^2 - r*r

	discr = cy->half_b * cy->half_b - cy->a * cy->c;
	if (discr < 0.0f || cy->a == 0.0f) // pas d'intersection réelle, ou rayon // à l'axe (A ≈ 0)
		return (t);

	if (sign == 0)
		t = (-cy->half_b - sqrtf(discr)) / cy->a;   // racine proche
	else if (sign == 1)
		t = (-cy->half_b + sqrtf(discr)) / cy->a;   // racine lointaine
	return (t);
}

int	is_t_in_limits(float t, t_cy *cy, const t_ray *r, t_hit *out)
{
	t_vector	p;
	float		tmax;

	tmax = out->t;
	if (t >= EPS && t <= tmax)
	{
		cy->m = cy->dv * t + cy->xv;
		if (cy->m >= 0.0f && cy->m <= cy->height)
		{
			p = v_add(r->o, v_scale(r->d, t));
			assign_hitpoint(t, p, transform_n(cy, p, r), out);
			return (1);
		}
	}
	return (0);
}