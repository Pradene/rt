#include "../../includes/minirt.h"

t_obj_type  check_obj_type(char *type)
{
    int                 i;
    static const char   *types[] = {"A", "C", "L", "sp", "pl", "cy", NULL};

    if (!type)
        return (ERROR);
    i = -1;
    while (types[++i])
    {
        if (!strcmp(types[i], type))
            return (i + 1);
    }
    return (ERROR);
}

int check_ambient_light(t_alight light)
{
    if (!check_color(light.color) || !check_brightness(light.brightness))
        return (0);
    return (1);
}

int ambient_light(char **args)
{
    t_data  *data;
    char    *tmp;

    data = get_data();
    if (string_array_size(args) != 3)
        return (0);
    if (data->alight.created)
        return (0);
    data->alight.brightness = strtofloat(args[1], &tmp);
    if (tmp != args[1] + strlen(args[1]))
        return (0);
    data->alight.color = strtov3(args[2]);
    data->alight.created = 1;
    if (!check_ambient_light(data->alight))
        return (0);
    return (1);
}

int check_camera(t_camera camera)
{
    if (!check_fov(camera.fov) || !check_direction(camera.direction))
        return (0);
    return (1);
}

int camera(char **args)
{
    t_data  *data;
    char    *tmp;

    data = get_data();
    if (string_array_size(args) != 4)
        return (0);
    if (data->camera.created)
        return (0);
    data->camera.position = strtov3(args[1]);
    data->camera.direction = strtov3(args[2]);
    data->camera.fov = (int)strtofloat(args[3], &tmp);
    data->camera.created = 1;
    if (!check_camera(data->camera))
        return (0);
    return (1);
}

int check_light(t_light light)
{
    if (!check_color(light.color) || !check_brightness(light.brightness))
        return (0);
    return (1);
}

int light(char **args)
{
    t_data  *data;
    char    *tmp;

    data = get_data();
    if (string_array_size(args) != 4)
        return (0);
    if (data->light.created)
        return (0);
    data->light.position = strtov3(args[1]);
    data->light.brightness = strtofloat(args[2], &tmp);
    data->light.color = strtov3(args[3]);
    data->light.created = 1;
    if (!check_light(data->light))
        return (0);
    return (1);
}

int sphere(char **args)
{
    t_obj_list  *obj;
    t_data      *data;
    char        *tmp;

    data = get_data();
    if (string_array_size(args) != 4)
        return (0);
    obj = malloc(sizeof(t_obj_list));
    if (!obj)
        return (0);
    obj->next = NULL;
    obj->object.type = SPHERE;
    obj->object.position = strtov3(args[1]);
    obj->object.diameter = strtofloat(args[2], &tmp);
    obj->object.color = strtov3(args[3]);
    add_objects(&data->objects, obj);
    return (1);
}

int plane(char **args)
{
    t_obj_list  *obj;
    t_data  *data;

    data = get_data();
    if (string_array_size(args) != 4)
        return (0);
    obj = malloc(sizeof(t_obj_list));
    if (!obj)
        return (0);
    obj->next = NULL;
    obj->object.type = PLANE;
    obj->object.position = strtov3(args[1]);
    obj->object.rotation = strtov3(args[2]);
    obj->object.color = strtov3(args[3]);
    add_objects(&data->objects, obj);
    return (1);
}

int cylinder(char **args)
{
    t_obj_list  *obj;
    t_data      *data;
    char        *tmp;

    data = get_data();
    if (string_array_size(args) != 6)
        return (0);
    obj = malloc(sizeof(t_obj_list));
    if (!obj)
        return (0);
    obj->next = NULL;
    obj->object.type = CYLINDER;
    obj->object.position = strtov3(args[1]);
    obj->object.rotation = strtov3(args[2]);
    obj->object.diameter = strtofloat(args[3], &tmp);
    obj->object.height = strtofloat(args[4], &tmp);
    obj->object.color = strtov3(args[5]);
    add_objects(&data->objects, obj);
    return (1);
}


int create_obj_type(char **args, t_obj_type type)
{
    int (*func[])() = {ambient_light, camera, light, sphere, plane, cylinder};

    return ((*func[type - 1])(args));
}

int create_obj(char *line)
{
    char        **args;
    t_obj_type  type;
    int         status;

    if (!line)
        return (0);
    args = ft_split(line, ' ');
    if (!args)
        return (0);
    if (!args[0])
        return (free_string_array(args), 1);
    type = check_obj_type(args[0]);
    if (type == ERROR)
        return (free_string_array(args), 0);
    status = create_obj_type(args, type);
    free_string_array(args);
    return (status);
}

void    create_objs(char **sa)
{
    t_data  *data;
    int     i;

    if (!sa)
        return ;
    i = -1;
    data = get_data();
    while (sa[++i])
    {
        if (!create_obj(sa[i]))
        {
            printf("Error during parsing at line %d\n", i + 1);
            break ;
        }
    }
}