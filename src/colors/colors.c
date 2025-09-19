#include "../inc/minirt.h"

void	rgb_rescale(t_rgb *colors, int type)
{
	if (type)
	{
		colors->s_r = ((float)colors->r) / 255;
		colors->s_g = ((float)colors->g) / 255;
		colors->s_b = ((float)colors->b) / 255;
	}
	else
	{
		colors->r = (int)(colors->s_r * 255);
		colors->g = (int)(colors->s_g * 255);
		colors->b = (int)(colors->s_b * 255);
	}
}

void	initialize_color(t_data *data, t_pixel *canvas)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	x = 0;
	while (x < W_WIDTH)
	{
		y = 0;
		while (y < W_HEIGHT)
		{
			canvas[i].colors.r = data->a.colors.r * data->a.ratio;
			canvas[i].colors.g = data->a.colors.g * data->a.ratio;;
			canvas[i].colors.b = data->a.colors.b * data->a.ratio;;
			rgb_rescale(&(canvas[i].colors), 1);
			canvas[i].color = rgb_to_hex(&(canvas[i].colors));
			i ++;
			y ++;
		}
		x ++;
	}
}

void	mix_colors(t_pixel *pixel, t_rgb color2)
{
	rgb_rescale(&color2, 1);
	pixel->colors.s_r *= color2.s_r;
	pixel->colors.s_g *= color2.s_g;
	pixel->colors.s_b *= color2.s_b;
	rgb_rescale(&(pixel->colors), 0);
	pixel->color = rgb_to_hex(&(pixel->colors));
}

void	test_mix_color(t_pixel *canvas, int i)
{
	float	s[3];
	//attention: melanger couleur "pure" avec couleur "pure" = noir, car multiplier nimp avec 0 = 0.
	s[0] = 0.3;	
	s[1] = 0.3;
	s[2] = 0.9;

	if (i > 288000 && i <= 620000) // objectif: melanger la couleur 1 avec ce que je lui donne ici en dur -> OK
	{
		canvas[i].colors.s_r *= s[0];
		canvas[i].colors.s_g *= s[1];
		canvas[i].colors.s_b *= s[2];
		rgb_rescale(&(canvas[i].colors), 0);
		//printf("int mix r = %d, g = %d, b = %d\n", canvas[i].colors.r, canvas[i].colors.g, canvas[i].colors.b);
		canvas[i].color = rgb_to_hex(&(canvas[i].colors));
	}
	else if (i > 620000)
	{
		canvas[i].colors.s_r = s[0];
		canvas[i].colors.s_g = s[1];
		canvas[i].colors.s_b = s[2];
		rgb_rescale(&(canvas[i].colors), 0);
		canvas[i].color = rgb_to_hex(&(canvas[i].colors));
	}
	// objectif: eclaircir -> apparemment il faut reequilibrer les 3 couleurs, mais selon quelle logique?
}