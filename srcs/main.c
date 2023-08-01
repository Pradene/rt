#include "../includes/parsing.h"

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

void    free_data()
{
    t_data  *data;

    data = get_data();
    free_objects(&data->objects);
}

int main(int ac, char **av)
{
    if (ac < 2)
        return (1);
    data_initialisation();
    parsing(av[1]);
    free_data();
    return (0);
}