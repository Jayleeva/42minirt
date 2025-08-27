#include "../inc/minirt.h"

static void	init_uppercases(t_data *data)
{
	data->A.ratio = -1.0; // unsigned?
	data->A.colors.R = -1; // unsigned?
	data->A.colors.G = -1; // unsigned?
	data->A.colors.B = -1; // unsigned?
	data->C.coord.x = 0.0;
	data->C.coord.y = 0.0;
	data->C.coord.z = 0.0;
	data->C.ornt.o_x = 0.0;
	data->C.ornt.o_y = 0.0;
	data->C.ornt.o_z = 0.0;
	data->C.fov = -1; // unsigned?
	data->L.coord.x = 0.0;
	data->L.coord.y = 0.0;
	data->L.coord.z = 0.0;
	data->L.ratio = -1.0; // unsigned?
}

void	init(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map = NULL;

	init_uppercases(data);
	//data->sp;
	//data->pl;
	//data->cy;
	//initialize_images(data);

}

int main(int argc, char **argv)
{
	t_data	data;

    test();
    init(&data);
    if (argc != 2)
        return (1);
    if (!is_valid(&data, argv[1]))
        return (1);
    initialize(&data, 5, 5);
    return (0);
}