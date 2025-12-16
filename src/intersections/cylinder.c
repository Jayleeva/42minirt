#include "../inc/minirt.h"

// out->t sert de tmax à l'entrée,
// on ne met à jour que si on trouve un t plus petit (plus proche)
static int	hit_cylinder_side(const t_ray *r, t_cy *cy, t_hit *out)
{
	float		t1;
	float		t2;
	int			hit = 0;

	// X = O - C : vecteur de la base du cylindre vers l'origine du rayon
	cy->X = v_sub(r->o, cy->coord);
	
	// Projections sur l'axe : dv = D·V, xv = X·V  (V DOIT être normalisé)
	cy->dv = v_dot(r->d, v_norm(cy->ornt));
	cy->xv = v_dot(cy->X, v_norm(cy->ornt));

	t1 = find_t(r, cy, 0);
	t2 = find_t(r, cy, 1);
	if (t1 == -1 || t2 == -1)
		return (0);
	// On teste dans l'ordre croissant (t1 puis t2)
	if (is_t_in_limits(t1, cy, r, out))
		hit = 1;
	if (is_t_in_limits(t2, cy, r, out))
		hit = 1;
	return (hit);
}

// Intersecte un plan cap (center, normal), 
// puis vérifie si le point est dans le disque (rayon cap->radius).
// Convention t : t in [tmin, out->t]. Normal supposée unitaire (V ou -V).
static int	hit_cylinder_cap(const t_ray *r, const t_cap *cap, t_hit *out)
{
	float denom;
	float t;
	t_vector p;

	// Si D·n ≈ 0 : rayon // au plan -> pas d'intersection stable
	denom = v_dot(r->d, cap->normal);
	if (fabsf(denom) < 1e-6f)
		return (0);

	// t = ((center - O)·n) / (D·n)
	t = v_dot(v_sub(cap->center, r->o), cap->normal) / denom;
	if (t < EPS || t > out->t)
		return (0);

	p = v_add(r->o, v_scale(r->d, t));

	// Test disque : distance au carré au centre ≤ r^2
	if (v_len2(v_sub(p, cap->center)) > cap->radius * cap->radius)
		return (0);

	out->t    = t;
	out->p    = p;
	out->n    = cap->normal; // déjà unitaire (utiliser V ou -V)
	if (v_dot(out->n, r->d) > 0.0f)
		out->n = v_scale(out->n, -1.0f);
	out->kind = CYLINDER;
	return (1);
}


// Teste le flanc puis les deux caps, en gardant le t le plus petit (via out->t).
// Préparer cap_lo et cap_hi ici évite un gros prototype et reste lisible.
int	hit_cylinder(const t_ray *r, t_cy *cy, t_hit *out)
{
	int   hit_any;
	t_cap cap_lo;
	t_cap cap_hi;

	hit_any = 0;

	// Flanc : principal contributeur. Si on trouve un hit, out->t est réduit (meilleur tmax pour les caps).
	if (hit_cylinder_side(r, cy, out))
		hit_any = 1;

	// Caps : (C, -V) et (C + V*height, +V)
	cap_lo.center = cy->coord;
	cap_lo.normal = v_scale(v_norm(cy->ornt), -1.0f);
	cap_lo.radius = cy->diameter * 0.5f;
	cap_hi.center = v_add(cy->coord, v_scale(v_norm(cy->ornt), cy->height));
	cap_hi.normal = v_norm(cy->ornt);
	cap_hi.radius = cap_lo.radius;

	// Chaque cap respecte la fenêtre [tmin, out->t] courante.
	if (hit_cylinder_cap(r, &cap_lo, out))
		hit_any = 1;
	if (hit_cylinder_cap(r, &cap_hi, out))
		hit_any = 1;
	return (hit_any);
}


/*
Cylinder hit – résumé des formules (V doit être unitaire) :
C : point de base du cylindre, V : axe, r : rayon (= diameter/2), height : longueur.
Ray : O + tD. On décompose D et X=(O−C) en composante // à V et composante ⟂ à V :
A = D − V(D·V) (direction “latérale”)
B = X − V*(X·V) (origine “latérale”)
Sur le flanc : || B + tA || = r → (A·A)t² + 2(A·B)t + (B·B−r²) = 0
On pose half_b = A·B pour éviter le facteur 2 : disc = half_b² − ac, avec a=A·A.
Filtre hauteur : m = (D·V)t + (X·V) doit être dans [0, height] (distance le long de l’axe).
Normale flanc : n = nrm( (P−C) − Vm ), orientée à l’opposé du rayon si besoin.
Caps : deux plans (C, −V) et (C+V*height, +V). On intersecte le plan, puis on teste le disque (|| P−center || ≤ r).
Convention t : à l’entrée, out->t = tmax courant. On n’écrit out que si on trouve mieux (t dans [tmin, out->t]).

*/
