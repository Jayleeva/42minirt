#include "../inc/minirt.h"

t_vector	v_minus_float(t_vector v, float f);

void assign_hitpoint(float t, const t_cy *cy, float m, t_point p, const t_ray *r, t_hit *out)
{
	t_vector	n;
	t_vector	tmp1;
	t_vector	tmp2;

	tmp1 = v_from_points(cy->coord, p);
	tmp2 = v_scale(cy->ornt, m);
	n = v_norm(v_sub(tmp1, tmp2));

	/*n = v_from_points(cy->coord, p);
	n = v_sub(n, v_scale(cy->ornt, m));
	n = v_norm(n);*/
	if (v_dot(n, r->d) > 0.0f)
		n = v_scale(n, -1.0f);
	out->t = t;
	out->p = p;
	out->n = n;
	out->kind = CYLINDER;

	   //N = nrm( P-C-V*m )
}

// out->t sert de tmax à l'entrée, on ne met à jour que si on trouve un t plus petit (plus proche)
static int	hit_cylinder_side(const t_ray *r, const t_cy *cy,
							 float tmin, t_hit *out)
{
	t_vector	X; //, A, B;
	float		rads, dv, xv;
	float		a, half_b, c, disc, sqrtd;
	float		t1, t2, m, t;
	t_point		p;
	int			hit = 0;
	float		tmax;

	// X = O - C : vecteur de la base du cylindre vers l'origine du rayon
	X = v_from_points(cy->coord, r->o);
	rads = cy->diameter * 0.5f;
	
	// Projections sur l'axe : dv = D·V, xv = X·V  (V DOIT être normalisé)
	dv = v_dot(r->d, v_norm(cy->ornt));
	xv = v_dot(X, v_norm(cy->ornt));

	// Quadratique sur le flanc : a t^2 + 2*half_b t + c = 0
	a = v_dot(r->d, r->d) - (dv * dv);	//   a   = D|D - (D|V)^2
	//a = v_dot(r->d, r->d); // NOPE
	//a = v_dot(v_sub(r->d, v_scale(cy->ornt, dv)), v_sub(r->d, v_scale(cy->ornt, dv))); // meme chose que A et A
	
	half_b = v_dot(r->d, X) - (dv * xv);	//   b/2 = D|X - (D|V)*(X|V) CLOOOOSE
	//half_b = v_dot(v_sub(r->d, v_scale(v_norm(cy->ornt), dv)), v_sub(X, v_scale(v_norm(cy->ornt), xv))); // meme chose que A et B

	//half_b = v_dot(r->d, X); // NOPE CASSE TOUTES LES AUTRES MAPS

	//half_b = v_dot(r->d, X) - v_dot(r->d, v_scale(r->d, dv)) - v_dot(X, v_scale(X, xv)); // NOPE 
	/*t_vector	tmp_rd = v_minus_float(r->d, dv * xv);
	t_vector	tmp_x = v_minus_float(X, dv * xv);
	half_b = v_dot(tmp_rd, tmp_x);*/
	//half_b = v_dot(v_scale(r->d, dv * xv), v_scale(X, dv * xv)); //NOPE
	//half_b = v_dot(v_scale(r->d, dv), v_scale(X, xv)); // NOPE
	//half_b = v_dot(v_scale(r->d, xv), v_scale(X, dv)); // NOPE

	//half_b = v_dot(v_sub(r->d, cy->ornt), v_sub(X, cy->ornt)); .// NOPE
	//half_b = v_dot(r->d, cy->ornt); // NOPE
	//half_b = v_dot(r->d, v_sub(X, v_scale(cy->ornt, xv))); // NOPE
	//half_b = v_dot(v_scale(cy->ornt, dv), v_scale(cy->ornt, xv)); // NOPE

	//half_b = v_dot(v_sub(r->d, v_scale(cy->ornt, dv)), v_sub(X, v_scale(cy->ornt, xv)));
	c = v_dot(X, X) - (xv * xv) - (rads * rads);	//   c   = X|X - (X|V)^2 - r*r
	//c = v_dot(X, X) - (rads * rads); // NOPE


	// Composantes perpendiculaires à l'axe (on “retire” l'axe)
	//A = v_sub(r->d, v_scale(cy->ornt, dv)); // A = D - V*(D·V)
	//B = v_sub(X, v_scale(cy->ornt, xv)); // B = X - V*(X·V)

	//a = v_dot(A, A);
	//half_b = v_dot(A, B);
	//c = v_dot(B, B) - rads * rads;

	disc = half_b * half_b - a * c;
	if (disc < 0.0f || a == 0.0f) // pas d'intersection réelle, ou rayon // à l'axe (A ≈ 0)
		return (0);

	sqrtd = sqrtf(disc);
	t1 = (-half_b - sqrtd) / a;   // racine proche
	t2 = (-half_b + sqrtd) / a;   // racine lointaine

	// On teste dans l'ordre croissant (t1 puis t2)
	tmax = out->t;
	if (t1 >= tmin && t1 <= tmax)
	{
		m = dv * t1 + xv;
		if (m >= 0.0f && m <= cy->height)
		{
			p = p_add_v(r->o, v_scale(r->d, t1));
			assign_hitpoint(t1, cy, m, p, r, out);
			hit = 1;
		}
	}
	tmax = out->t;
	if (t2 >= tmin && t2 <= tmax)
	{
		m = dv * t2 + xv;
		if (m >= 0.0f && m <= cy->height)
		{
			p = p_add_v(r->o, v_scale(r->d, t2));
			assign_hitpoint(t2, cy, m, p, r, out);
			hit = 1;
		}
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