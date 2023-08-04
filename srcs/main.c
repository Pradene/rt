#include "../includes/minirt.h"

t_data  *get_data(void)
{
    static t_data   data;

    return (&data);
}

void    data_initialisation()
{
    t_data  *data;

    data = get_data();
    data->objects = NULL;
    data->camera.created = 0;
    data->light.created = 0;
    data->alight.created = 0;
}

int free_data()
{
    t_data  *data;

    data = get_data();
    free_objects(&data->objects);
    if (data->id && data->img.image)
	    mlx_destroy_image(data->id, data->img.image);
	if (data->id && data->win)
        mlx_destroy_window(data->id, data->win);
	if (data->id)
        mlx_destroy_display(data->id);
    free(data->id);
    exit(EXIT_SUCCESS);
    return (0);
}

int main(int ac, char **av)
{
    if (ac < 2)
        return (1);
    data_initialisation();
    parsing(av[1]);
    renderer("miniRT");
    render();
    free_data();
    return (0);
}
