#include "../inc/minirt.h"

// out->t sert de tmax à l'entrée, on ne met à jour que si on trouve un t plus petit (plus proche)
static int	hit_cylinder_side(const t_ray *r, const t_cy *cy,
							 float tmin, t_hit *out)
{
	t_vector X, A, B;
	float    rads, dv, xv;
	float    a, half_b, c, disc, sqrtd;
	float    t1, t2, m, t;
	t_point  p;
	t_vector n;
	int      hit;

	hit = 0;

	// X = O - C : vecteur de la base du cylindre vers l'origine du rayon
	X = v_from_points(cy->coord, r->o);
	rads = cy->diameter * 0.5f;

	// Projections sur l'axe : dv = D·V, xv = X·V  (V DOIT être normalisé)
	dv = v_dot(r->d, cy->ornt);
	xv = v_dot(X, cy->ornt);

	// Composantes perpendiculaires à l'axe (on “retire” l'axe)
	A = v_sub(r->d, v_scale(cy->ornt, dv)); // A = D - V*(D·V)
	B = v_sub(X, v_scale(cy->ornt, xv)); // B = X - V*(X·V)

	// Quadratique sur le flanc : a t^2 + 2*half_b t + c = 0
	a = v_dot(A, A);
	half_b = v_dot(A, B);
	c = v_dot(B, B) - rads * rads;

	disc = half_b * half_b - a * c;
	if (disc < 0.0f || a == 0.0f) // pas d'intersection réelle, ou rayon // à l'axe (A ≈ 0)
		return (0);

	sqrtd = sqrtf(disc);
	t1 = (-half_b - sqrtd) / a;   // racine proche
	t2 = (-half_b + sqrtd) / a;   // racine lointaine

	// On teste dans l'ordre croissant (t1 puis t2)
	t = t1;
	while (1)
	{
		// fenêtre valide : devant la caméra et plus proche que le meilleur hit courant
		if (t >= tmin && t <= out->t)
		{
			// m = position du point le long de l'axe (0 = base, height = cap haut)
			m = dv * t + xv;
			if (m >= 0.0f && m <= cy->height) // coupe le flanc à l'intérieur des caps ?
			{
				p = p_add_v(r->o, v_scale(r->d, t)); // point d'impact
				// normale du flanc : n = nrm( (P-C) - V*m )
				n = v_from_points(cy->coord, p);
				n = v_sub(n, v_scale(cy->ornt, m));
				n = v_norm(n);
				// convention : normale opposée au rayon (évite faces “à l’envers”)
				if (v_dot(n, r->d) > 0.0f)
					n = v_scale(n, -1.0f);

				// Mise à jour du meilleur hit
				out->t = t;
				out->p = p;
				out->n = n;
				out->kind = CYLINDER;
				hit = 1;
				// pas de break : on laisse la boucle tester t2 au cas où
			}
		}
		if (t == t2)
			break ;
		t = t2;
	}
	return (hit);
}

// Intersecte un plan cap (center, normal), puis vérifie si le point est dans le disque (rayon cap->radius).
// Convention t : t in [tmin, out->t]. Normal supposée unitaire (V ou -V).
static int	hit_cylinder_cap(const t_ray *r, const t_cap *cap,
							float tmin, t_hit *out)
{
	float denom;
	float t;
	t_point p;

	// Si D·n ≈ 0 : rayon // au plan -> pas d'intersection stable
	denom = v_dot(r->d, cap->normal);
	if (fabsf(denom) < 1e-6f)
		return (0);

	// t = ((center - O)·n) / (D·n)
	t = v_dot(v_from_points(r->o, cap->center), cap->normal) / denom;
	if (t < tmin || t > out->t)
		return (0);

	p = p_add_v(r->o, v_scale(r->d, t));

	// Test disque : distance au carré au centre ≤ r^2
	if (v_len2(v_from_points(cap->center, p)) > cap->radius * cap->radius)
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
int	hit_cylinder(const t_ray *r, const t_cy *cy, float tmin, t_hit *out)
{
	int   hit_any;
	t_cap cap_lo;
	t_cap cap_hi;

	hit_any = 0;

	// Flanc : principal contributeur. Si on trouve un hit, out->t est réduit (meilleur tmax pour les caps).
	if (hit_cylinder_side(r, cy, tmin, out))
		hit_any = 1;

	// Caps : (C, -V) et (C + V*height, +V)
	cap_lo.center = cy->coord;
	cap_lo.normal = v_scale(cy->ornt, -1.0f);
	cap_lo.radius = cy->diameter * 0.5f;
	cap_hi.center = p_add_v(cy->coord, v_scale(cy->ornt, cy->height));
	cap_hi.normal = cy->ornt;
	cap_hi.radius = cap_lo.radius;

	// Chaque cap respecte la fenêtre [tmin, out->t] courante.
	if (hit_cylinder_cap(r, &cap_lo, tmin, out))
		hit_any = 1;
	if (hit_cylinder_cap(r, &cap_hi, tmin, out))
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