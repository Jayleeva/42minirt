#ifndef MINIRT_H
# define MINIRT_H 
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>
# include "libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
    char	**map;
}           t_data;

void	initialize(char **tab, size_t len, int nelem);
int	    on_destroy(t_data *data);

#endif