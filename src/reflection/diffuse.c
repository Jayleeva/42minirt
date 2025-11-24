#include "../inc/minirt.h"

/*
 Vérifie si le point d'impact est dans l'ombre.
 On envoie un rayon du point vers la lumière et on regarde
 s'il touche un objet avant d'arriver à la lumière.
*/
static int	is_in_shadow(t_data *d, t_hit *hit)
{
	t_ray		shadow;
	t_hit		tmp;
	t_vector	to_light;
	float		dist_light;

	to_light = v_from_points(hit->p, d->l.coord);
	dist_light = v_len(to_light);
	if (dist_light <= 0.0f)
		return (0);
	shadow.o = p_add_v(hit->p, v_scale(hit->n, 1e-3f));
	shadow.d = v_scale(to_light, 1.0f / dist_light);
	tmp.t = dist_light;
	tmp.idx = -1;
	tmp.kind = -1;
	if (world_hit(d, &shadow, EPS, dist_light, &tmp))
		return (1);
	return (0);
}

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
diffuse = max(dot(N, L), 0) * light_ratio
N = normale, L = direction vers la lumière.
*/
static float	compute_diffuse(t_data *d, t_hit *h, t_vector n)
{
	t_vector	l;
	float		diff;

	l = v_from_points(h->p, d->l.coord);
	l = v_norm(l);
	diff = v_dot(n, l);
	if (diff < 0.0f || is_in_shadow(d, h))
		diff = 0.0f;
	return (diff * d->l.ratio);
}

/*
Le highlight.
On réfléchit L autour de N, puis on mesure l'alignement
entre R et V :
spec = ks * light_ratio * max(dot(R, V), 0)^shiny
*/
static float	compute_specular(t_data *d, t_hit *h, t_vector n)
{
	t_vector	l;
	t_vector	v;
	t_vector	r;
	float		spec;

	l = v_norm(v_from_points(h->p, d->l.coord));
	v = v_norm(v_from_points(h->p, d->c.coord));
	r = v_norm(v_reflect(l, n));
	spec = v_dot(r, v);
	if (spec < 0.0f || is_in_shadow(d, h))
		return (0.0f);
	spec = powf(spec, d->spec.shiny);
	spec *= d->spec.ks * d->l.ratio;
	return (spec);
}

/*
Calcule la couleur finale au point d'impact :
1) on convertit l'objet et l'ambient en [0,1]
2) on calcule diffuse + specular
3) résult = objet * (ambient + diffuse) + specular (highlight)
*/
t_rgb	compute_lighting(t_data *d, t_hit *h, t_rgb obj)
{
	t_rgb		obj_s;
	t_rgb		amb_s;
	t_vector	n;
	float		diffuse;
	float		spec;

	obj_s = obj;
	rgb_rescale(&obj_s, 1);
	amb_s = d->a.colors;
	rgb_rescale(&amb_s, 1);
	amb_s.s_r *= d->a.ratio;
	amb_s.s_g *= d->a.ratio;
	amb_s.s_b *= d->a.ratio;
	n = v_norm(h->n);
	diffuse = compute_diffuse(d, h, n);
	spec = compute_specular(d, h, n);
	obj_s.s_r = obj_s.s_r * (amb_s.s_r + diffuse) + spec;
	obj_s.s_g = obj_s.s_g * (amb_s.s_g + diffuse) + spec;
	obj_s.s_b = obj_s.s_b * (amb_s.s_b + diffuse) + spec;
	if (obj_s.s_r > 1.0f)
		obj_s.s_r = 1.0f;
	if (obj_s.s_g > 1.0f)
		obj_s.s_g = 1.0f;
	if (obj_s.s_b > 1.0f)
		obj_s.s_b = 1.0f;
	rgb_rescale(&obj_s, 0);
	return (obj_s);
}
