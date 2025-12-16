#include "../inc/minirt.h"

float	compute_cy_discr(const t_ray *r, t_cy *cy)
{
	float	rads;
	float	discr;

	rads = cy->diameter * 0.5f;
	cy->X = v_sub(r->o, cy->coord);
	cy->dv = v_dot(r->d, v_norm(cy->ornt));
	cy->xv = v_dot(cy->X, v_norm(cy->ornt));
	cy->a = v_dot(r->d, r->d) - (cy->dv * cy->dv);
	cy->half_b = v_dot(r->d, cy->X) - (cy->dv * cy->xv);
	cy->c = v_dot(cy->X, cy->X) - (cy->xv * cy->xv) - (rads * rads);
	discr = cy->half_b * cy->half_b - cy->a * cy->c;
	return (discr);
}

// out->t sert de tmax à l'entrée,
// on ne met à jour que si on trouve un t plus petit (plus proche)
static int	hit_cylinder_side(const t_ray *r, t_cy *cy, t_hit *out)
{
	float		t1;
	float		t2;
	float		discr;
	int			hit;

	hit = 0;
	discr = compute_cy_discr(r, cy);
	if (discr < 0.0f || cy->a == 0.0f)
		return (hit);
	t1 = (-cy->half_b - sqrtf(discr)) / cy->a;
	t2 = (-cy->half_b + sqrtf(discr)) / cy->a;
	if (is_cy_t_in_limits(t1, cy, r, out))
		hit = 1;
	if (is_cy_t_in_limits(t2, cy, r, out))
		hit = 1;
	return (hit);
}

// Intersecte un plan cap (center, normal), 
// puis vérifie si le point est dans le disque (rayon cap->radius).
// Convention t : t in [tmin, out->t]. Normal supposée unitaire (V ou -V).
static int	hit_cylinder_cap(const t_ray *r, const t_cap *cap, t_hit *out)
{
	float		denom;
	float		t;
	t_vector	p;

	denom = v_dot(r->d, cap->normal);
	if (fabsf(denom) < 1e-6f)
		return (0);
	t = v_dot(v_sub(cap->center, r->o), cap->normal) / denom;
	if (t < EPS || t > out->t)
		return (0);
	p = v_add(r->o, v_scale(r->d, t));
	if (v_len2(v_sub(p, cap->center)) > cap->radius * cap->radius)
		return (0);
	out->t = t;
	out->p = p;
	out->n = cap->normal;
	if (v_dot(out->n, r->d) > 0.0f)
		out->n = v_scale(out->n, -1.0f);
	out->kind = CYLINDER;
	return (1);
}

// Teste le flanc puis les deux caps, en gardant le t le plus petit.
// Préparer cap_lo et cap_hi ici évite un gros prototype et reste lisible.
int	hit_cylinder(const t_ray *r, t_cy *cy, t_hit *out)
{
	int		hit_any;
	t_cap	cap_lo;
	t_cap	cap_hi;

	hit_any = 0;
	if (hit_cylinder_side(r, cy, out))
		hit_any = 1;
	cap_lo.center = cy->coord;
	cap_lo.normal = v_scale(v_norm(cy->ornt), -1.0f);
	cap_lo.radius = cy->diameter * 0.5f;
	cap_hi.center = v_add(cy->coord, v_scale(v_norm(cy->ornt), cy->height));
	cap_hi.normal = v_norm(cy->ornt);
	cap_hi.radius = cap_lo.radius;
	if (hit_cylinder_cap(r, &cap_lo, out))
		hit_any = 1;
	if (hit_cylinder_cap(r, &cap_hi, out))
		hit_any = 1;
	return (hit_any);
}
