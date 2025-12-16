#include "../inc/minirt.h"

/*
diffuse = max(dot(N, L), 0) * light_ratio
N = normale, L = direction vers la lumière.
*/
float	compute_diffuse(t_data *d, t_hit *h, t_vector n)
{
	t_vector	l;
	float		diff;

	l = v_from_points(h->p, d->l.coord);
	l = v_norm(l);
	diff = v_dot(n, l);
	if (diff <= 0.0f)
		diff = 0.0f;
	return (diff * d->l.ratio);
}

