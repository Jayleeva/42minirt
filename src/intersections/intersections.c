#include "../inc/minirt.h"

// Parcourt toutes les sphères de la scène et cherche la plus proche
// parmi celles que le rayon intersecte.
// Retourne 1 si au moins une sphère est touchée, 0 sinon.
static int	try_spheres(t_data *d, const t_ray *r, float tmin, t_hit *best)
{
	t_hit	tmp;
	int		found;
	int		i;
	//int		index;

	//index = best->idx;
	found = 0;
	i = 0;
	while (i < d->n_lel[0])
	{
		// On teste si le rayon touche la sphère i
		//if (index != i) // protection pour qu'il ne se cherche pas lui-meme NOPE enleve l'ombre de la sphere
		//{		
			if (hit_sphere(r, &d->sp[i], tmin, best->t, &tmp))
			{
				// Si oui -> mise à jour du "meilleur" hit (le plus proche)
				found = 1;
				*best = tmp;
				best->idx = i;
			}
		//}
		i++;
	}
	return (found);
}

static int	try_cylinders(t_data *d, const t_ray *r, float tmin, t_hit *best)
{
  	t_hit	tmp;
	int		found;
	int		i;
	//int		index;

	//index = best->idx;
	found = 0;
	i = 0;
  	while (i < d->n_lel[2])
	{
		tmp = *best;
		//if (index != i) // protection pour qu'il ne se cherche pas lui-meme NOPE enleve l'ombre du cylindre
		//{
			if (hit_cylinder(r, &d->cy[i], tmin, &tmp))
			{
				*best = tmp;
				best->idx = i;
				found = 1;
			}
		//}
		i++;
	}
	return (found);
}

static int	try_planes(t_data *d, const t_ray *r, float tmin, t_hit *best)
{
	t_hit	tmp;
	int		found;
	int		i;
	//int		index;

	//index = best->idx;
	found = 0;
	i = 0;
	while (i < d->n_lel[1])
	{
		tmp = *best;
		//if (index != i) // protection pour qu'il ne se cherche pas lui-meme NOPE fout la merde sur certaines maps, meme si regle en partie l'acne sur d'autres
		//{		
			if (hit_plane(r, &d->pl[i], tmin, best->t, &tmp))
			{
				//printf("touch plane from plane, index = %d and i = %d\n", index, i);
				found = 1;
				*best = tmp;
				best->idx = i;
			}
		//}
		i++;
	}
	return (found);
}


// Cherche l'intersection la plus proche entre le rayon et tous les objets du monde
// (pour l’instant seulement les sphères). 
// Initialise "h" avec les infos du hit le plus proche trouvé.
// Retourne 1 si un objet est touché, 0 sinon.
int	world_hit(t_data *d, const t_ray *r, float tmin, float tmax, t_hit *h)
{
	int	any;

	h->t = tmax;
	h->idx = -1;
	h->kind = -1;
	any = 0;
	if (try_spheres(d, r, tmin, h))
		any = 1;
	if (try_cylinders(d, r, tmin, h))
		any = 1;
	if (try_planes(d, r, tmin, h))
		any = 1;
	return (any);
}

int	world_hit_shadow(t_data *d, const t_ray *r, float tmin, float tmax, t_hit *h)
{
	int	any;

	h->t = tmax;
	//h->idx = -1;
	//h->kind = -1;
	any = 0;
	if (try_spheres(d, r, tmin, h))
		any = 1;
	if (try_cylinders(d, r, tmin, h))
		any = 1;
	if (try_planes(d, r, tmin, h))
		any = 1;
	return (any);
}

/*
Explications :
if ue des sphères,
donc world_hit appelle try_spheres.

- try_spheres parcourt toutes les sphères de d->sp[]
- Pour chaque sphère, il appelle hit_sphere()
- Si une intersection valide est trouvée :
    -> on met à jour "best" avec ce nouvel impact
    -> on retient son index
- À la fin, on retourne 1 si au moins une sphère a été touchée

world_hit = gestion de tous les objets
try_spheres = gestion spécifique des sphères
hit_sphere = calcul mathématique de l’intersection avec une sphère
*/
