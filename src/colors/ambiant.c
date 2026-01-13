/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyglardo <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:56:42 by cyglardo          #+#    #+#             */
/*   Updated: 2026/01/13 16:58:54 by cyglardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Applique un ratio a une couleur.
t_rgb	ratio_color(t_rgb color, float ratio)
{
	t_rgb	res;

	res.r = color.r * ratio;
	res.g = color.g * ratio;
	res.b = color.b * ratio;
	return (res);
}

// Applique la couleur de la lumiere ambiante.
void	initialize_color(t_data *data, t_pixel *canvas, int i)
{
	t_rgb	amb;

	amb = ratio_color(data->a.colors, data->a.ratio);
	canvas[i].colors.r = amb.r;
	canvas[i].colors.g = amb.g;
	canvas[i].colors.b = amb.b;
	rgb_rescale(&(canvas[i].colors), 1);
	canvas[i].color = rgb_to_hex(&(canvas[i].colors));
}
