/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:56:42 by cyglardo          #+#    #+#             */
/*   Updated: 2025/09/30 14:42:44 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Envoie un rayon sur le pixel recu et verifie si on y trouve des elements.
// Si oui, lance le calcul de la couleur finale, lumieres comprises
void	cast_ray(t_data *data, int i, int x, int y)
{
	t_ray	r;
	t_hit	h;
	t_rgb	obj;
	t_rgb	final;

	h.tmax = 1e30f;
	r = make_primary_ray(data, x, y);
	if (world_hit(data, &r, 1e30f, &h))
	{
		if (h.kind == SPHERE)
			obj = data->sp[h.idx].colors;
		else if (h.kind == CYLINDER)
			obj = data->cy[h.idx].colors;
		else
			obj = data->pl[h.idx].colors;
		final = compute_lighting(data, &h, obj);
		data->canvas[i].colors = final;
		data->canvas[i].color = rgb_to_hex(&(data->canvas[i].colors));
	}
	else
		initialize_color(data, data->canvas, i);
}

// Donne la couleur recue aux coordonnees de pixel recues.
void	ft_put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*pxl;

	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{
		pxl = data->addr + (y * data->size + x * (data->bpp / 8));
		*(unsigned int *)pxl = color;
	}
}

// Parcourt chaque pixel et lance l'envoi de rayon
// puis l'attribuation de couleur.
void	loop_on_pixels(t_data *d)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = 0;
	while (x < W_WIDTH)
	{
		y = 0;
		while (y < W_HEIGHT)
		{
			cast_ray(d, i, x, y);
			ft_put_pixel(&(d->img), x, y, d->canvas[i].color);
			i ++;
			y ++;
		}
		x ++;
	}
}

// Alloue la place pour le canvas, cree une image 
//  et en recupere l'adresse pour l'attribution de couleur des pixels,
// lance la preparation de la camera, l'initialisation de la couleur 
//  de la lumiere ambiante, l'iteration sur chaque pixel;
// affiche l'image sur la fenêtre. 
int	ray_tracing(t_data *d)
{
	int		*bpp;
	int		*size;
	int		*endian;

	d->img.endian = 1;
	d->img.size = W_WIDTH;
	d->img.bpp = 1;
	bpp = &(d->img).bpp;
	size = &(d->img).size;
	endian = &(d->img).endian;
	d->canvas = malloc((W_HEIGHT * W_WIDTH + 1) * sizeof(t_pixel));
	if (!d->canvas)
		return (0);
	d->img.img_ptr = mlx_new_image(d->mlx_ptr, W_WIDTH, W_HEIGHT);
	d->img.addr = mlx_get_data_addr(d->img.img_ptr, bpp, size, endian);
	cam_prepare_view(d);
	loop_on_pixels(d);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img.img_ptr, 0, 0);
	return (1);
}
