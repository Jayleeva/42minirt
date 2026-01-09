#include "../inc/minirt.h"

static t_vector	compute_n(const t_cy *cy, t_vector p, const t_ray *r)
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

static void	update_hitpoint(float t, t_vector p, t_vector n, t_hit *out)
{
	out->t = t;
	out->p = p;
	out->n = n;
	out->kind = CYLINDER;
}

int	is_cy_t_in_limits(float t, t_cy *cy, const t_ray *r, t_hit *out)
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
			update_hitpoint(t, p, compute_n(cy, p, r), out);
			return (1);
		}
	}
	return (0);
}
