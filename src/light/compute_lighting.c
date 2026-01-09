#include "../inc/minirt.h"

static t_rgb	check_edges(t_rgb *obj)
{
	if (obj->s_r > 1.0f)
		obj->s_r = 1.0f;
	if (obj->s_g > 1.0f)
		obj->s_g = 1.0f;
	if (obj->s_b > 1.0f)
		obj->s_b = 1.0f;
	rgb_rescale(obj, 0);
	return (*obj);
}

/*
 Vérifie si le point d'impact est dans l'ombre.
 On envoie un rayon du point vers la lumière et on regarde
 s'il touche un objet avant d'arriver à la lumière.
*/
static int	is_in_shadow(t_data *d, t_hit *hit)
{
	t_ray		shadow;
	t_vector	from_light;
	float		dist_light;

	from_light = v_sub(hit->p, d->l.coord);
	dist_light = v_len(from_light);
	if (dist_light <= EPS)
		return (0);
	shadow.o = d->l.coord;
	shadow.d = v_norm(from_light);
	if (world_hit_shadow(d, &shadow, dist_light, hit))
		return (1);
	return (0);
}

/*
Calcule la couleur finale au point d'impact :
1) on convertit l'objet et l'ambient en [0,1]
2) on calcule diffuse + specular
3) résult = objet * (ambient + diffuse) + specular (highlight)
*/
t_rgb	compute_lighting(t_data *d, t_hit *h, t_rgb obj)
{
	float		diffuse;
	float		spec;
	t_rgb		obj_s;
	t_rgb		amb_s;

	diffuse = compute_diffuse(d, h, h->n);
	spec = compute_specular(d, h, h->n);
	if (is_in_shadow(d, h))
	{
		diffuse = 0.f;
		spec = 0.f;
	}
	obj_s = obj;
	rgb_rescale(&obj_s, 1);
	amb_s = ratio_color(d->a.colors, d->a.ratio);
	rgb_rescale(&amb_s, 1);
	obj_s.s_r = obj_s.s_r * (amb_s.s_r + diffuse) + spec;
	obj_s.s_g = obj_s.s_g * (amb_s.s_g + diffuse) + spec;
	obj_s.s_b = obj_s.s_b * (amb_s.s_b + diffuse) + spec;
	return (check_edges(&obj_s));
}
