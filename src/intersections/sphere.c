#include "../inc/minirt.h"
// Vérifie si un rayon (r) intersecte une sphère (s).
// Si oui, stocke les infos d’intersection dans out (point, normale, distance, type)
// Retourne 1 si hit, 0 sinon.
int	hit_sphere(const t_ray *r, const t_sp *s, float tmax, t_hit *out)
{
	t_vector	oc; // vecteur entre origine du rayon et centre de la sphère
	float		a, half_b, c, disc, sqrtd, t;

	// oc = (centre - origine du rayon)
	oc = v_sub(r->o, s->coord);

	// a = D·D (longueur au carré de la direction du rayon)
	a = v_dot(r->d, r->d);

	// half_b = (oc·D), correspond au terme "b/2" de l’équation quadratique
	half_b = v_dot(oc, r->d);

	// c = (oc·oc) - r^2 (distance au carré entre origine et centre moins rayon²)
	c = v_dot(oc, oc) - (s->diameter * 0.5f) * (s->diameter * 0.5f);

	// discriminant = (b/2)^2 - a*c
	disc = half_b * half_b - a * c;
	if (disc < 0.0f)
		return (0); // pas de solution réelle -> pas d’intersection

	sqrtd = sqrtf(disc);

	// première racine (la plus proche)
	t = (-half_b - sqrtd) / a;

	if (t < EPS || t > tmax) // hors des bornes -> tester la seconde
	{
		t = (-half_b + sqrtd) / a;
		if (t < EPS || t > tmax)
			return (0); // aucune racine valide -> pas de hit
	}
	// On a trouvé une intersection valide
	out->t = t; // distance le long du rayon
	out->p = v_add(r->o, v_scale(r->d, t)); // point d’impact : origine + t*direction
	out->n = v_norm(v_sub(out->p, s->coord)); // normale = (P - centre)/|...|
	
	// Si la normale est tournée vers l’intérieur, on l’inverse
	if (v_dot(out->n, r->d) > 0.0f)
		out->n = v_scale(out->n, -1.0f);
	out->kind = SPHERE;
	return (1);
}

/*
Intersection rayon/sphère 

· = produit scalaire
a = D·D -> ça veut dire le produit scalaire du vecteur direction avec lui-même, donc en fait la longueur au carré de D.

|V| = norme (longueur) du vecteur.
V·V = produit scalaire du vecteur avec lui-même.
Du coup : |V|² = V·V.

Une sphère est définie par :
 - son centre C
 - son rayon r

Un rayon est défini par :
 - une origine O
 - une direction D

Un point P est sur la sphère si :
    |P - C| = r
et sur le rayon si :
    P = O + tD   (t >= 0)

-> En combinant : |O + tD - C|² = r²

Ce qui donne une équation quadratique en t :
    a*t² + 2*half_b*t + c = 0

où :
    a       = D·D
    half_b  = (O - C)·D
    c       = (O - C)·(O - C) - r²

On calcule le discriminant :
    disc = half_b² - a*c

 - Si disc < 0 -> pas de solutions réelles → pas d’intersection
 - Si disc >= 0 -> il existe 1 ou 2 solutions (racines)

On choisit la plus petite racine positive comprise entre [tmin, tmax].
Cela évite de prendre une intersection derrière la caméra ou trop lointaine.

Enfin :
 - Le point d’impact est : P = O + tD
 - La normale est : N = normalize(P - C)
   (inversée si elle pointe du mauvais côté, pour être cohérente avec l’éclairage)

Résumé de la formule :
    a   = D·D
    b/2 = (O-C)·D
    c   = (O-C)·(O-C) - r²

https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm

*/
