#include "../inc/minirt.h"

// Transforme les int de 0 a 255 en float de 0.0 a 1.0 si type == 1, et l'inverse si type == 0.
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

// Cherche la premiere valeur du rgb (ignore les premiers zeros)
int	get_n(int *tmp)
{
	int	n;

	n = 0;
	while (n < 6)
	{
		if (tmp[n] > 0)
			break ;
		n ++;
	}
	return (n);
}

// Utils de la fonction rgb_to_hex: transforme les decimal (recus sous forme de string) en hexadecimal
void	rgb_to_hex_utils(int *tmp, int n, char *s)
{
	int	j;
	int	i;

	j = n;
	i = 0;
	while (j < 6)
	{
		if (tmp[j] > 9)
			s[i] = tmp[j] + 'A' - 10;
		else
			s[i] = tmp[j] + '0';
		i ++;
		j ++;
	}
	s[6 - n] = '\0';
}

// Transforme le code rgb en format hexadecimal.
int	rgb_to_hex(t_rgb *colors)
{
	int		tmp[6];
	char	*s;
	int		ret;
	int		n;

	tmp[0] = colors->r / 16;
	tmp[1] = colors->r % 16;
	tmp[2] = colors->g / 16;
	tmp[3] = colors->g % 16;
	tmp[4] = colors->b / 16;
	tmp[5] = colors->b % 16;
	n = get_n(tmp);
	if (n == 6)
		return (0);
	else
	{
		s = malloc((6 - n + 1) * sizeof(char));
		if (!s)
			return (-1);
	}
	rgb_to_hex_utils(tmp, n, s);
	ret = ft_atoi_base(s, 16);
	free(s);
	return (ret);
}
