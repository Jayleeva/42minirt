#include "../inc/minirt.h"

/*
Calcule le vecteur réfléchi de v autour de la normale n.
Formule : r = v - 2 * dot(v, n) * n
*/
static t_vector	v_reflect(t_vector v, t_vector n)
{
	t_vector	r;
	float		dotvn;
	t_vector	tmp;

	dotvn = v_dot(v, n);
	tmp = v_scale(n, 2.0f * dotvn);
	r = v_sub(tmp, v);
	return (r);
}

/*
Le highlight.
On réfléchit L autour de N, puis on mesure l'alignement
entre R et V :
spec = ks * light_ratio * max(dot(R, V), 0)^shiny
*/
float	compute_specular(t_data *d, t_hit *h, t_vector n)
{
	t_vector	l;
	t_vector	v;
	t_vector	r;
	float		spec;

	l = v_norm(v_from_points(h->p, d->l.coord));
	v = v_norm(v_from_points(h->p, d->c.coord));
	r = v_norm(v_reflect(l, n));
	spec = v_dot(r, v);
	if (spec <= 0.0f)
		return (0.0f);
	spec = powf(spec, d->spec.shiny);
	spec *= d->spec.ks * d->l.ratio;
	return (spec);
}