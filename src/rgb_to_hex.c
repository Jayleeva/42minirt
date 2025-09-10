#include "../inc/minirt.h"

//{ "red" , 0xff0000 }
//{ "green" , 0xff00 }
//{ "blue" , 0xff }

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

int	rgb_to_hex(t_pixel pixel)
{
	int		tmp[6];
	char	*s;
	int		ret;
	int		n;

	tmp[0] = pixel.colors.r / 16;
	tmp[1] = pixel.colors.r % 16;
	tmp[2] = pixel.colors.g / 16;
	tmp[3] = pixel.colors.g % 16;
	tmp[4] = pixel.colors.b / 16;
	tmp[5] = pixel.colors.b % 16;
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