#include "../inc/minirt.h"

int check_config(t_data *data, char *el)
{
    if (el[0] == 'A')
        return (check_A(data, el));
    else if (el[0] == 'C')
        return (check_C(data, el));
    else if (el[0] == 'L')
        return (check_L(data, el));
    /*else if (!ft_strncmp(el, "sp", 2))
        return (check_sp(data, el));
    else if (!ft_strncmp(el, "pl", 2))
        return (check_pl(data, el));
    else if (!ft_strncmp(el, "cy", 2))
        return (check_cy(data, el));*/
    else
        return (0);
    return (1);
}

//chaque element peut etre separe de 1 ou plusieurs retour a la ligne
//chaque information de l'element peut etre separe de 1 ou plusieurs espaces
// la premier info doit etre le type, les suivantes dans l'ordre exige par le type
// at least one: plane (pl), sphere (sp), cylinder (cy) order is not important
// strictly one: ambiant lighting (A), camera (C), light (L). order is not important
int is_map_valid(t_data *data, int fd, int nelem)
{
    char    *line;
    char    *used;
    int     i;

    used = NULL;
    if (!alloc_ptr(data->map, used, nelem))
        return (0);
    line = NULL;
    i = 0;
    while (get_next_line(fd))
    {
        if (!(line[0] == '\n'))
        {
            if (!is_usable(line, used, i))
                return (0);
            if (!check_config(data, line))
                return (0);
        }
        i ++;
    }
    if (is_element_missing(used))
        return (0);
    close(fd);
    free(line);
    free(used);
    return (1);
}

int is_valid(t_data *data, char *s)
{
    int fd;
    int nelem;

    if (!is_format_valid(s, ".rt"))
    {
        perror("Error\n file format invalid.\n");
        return (0);
    }
    fd = open(s, O_RDONLY);
    if (fd < 0)
    {
        perror("Error\n file invalid.\n");
        return (0);
    }
    nelem = count_elem(fd);
    close(fd);
    fd = open(s, O_RDONLY);
    if (fd < 0)
    {
        perror("Error\n file could not open.\n");
        return (0);
    }
    if (!is_map_valid(data, fd, nelem))
    {
        perror("Error\n map invalid.\n");
        return (0);
    }
    return (1);
}