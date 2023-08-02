#include "../../includes/minirt.h"

void    free_objects(t_obj_list **lst)
{
    t_obj_list  *tmp;

    if (!lst)
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        free(*lst);
        (*lst) = tmp;
    }
}

static t_obj_list   *last_objects(t_obj_list *lst)
{
    t_obj_list  *tmp;

    if (!lst)
        return (NULL);
    tmp = lst;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

void    add_objects(t_obj_list **lst, t_obj_list *new)
{
    t_obj_list	*tmp;

	if (!lst)
        return ;
	if (*lst)
	{
		tmp = last_objects(*lst);
		tmp->next = new;
	}
	else
    {
		*lst = new;
    }
}

void    print_color(v3 color)
{
    printf("    color: r = %d, g = %d, b = %d\n", \
    (int)color.r, (int)color.g, (int)color.b);
}

void    print_pos(v3 pos)
{
    printf("    pos: x = %lf, y = %lf, z = %lf\n", pos.x, pos.y, pos.z);
}

void    print_rotation(v3 rotation)
{
    printf("    rotation: x = %lf, y = %lf, z = %lf\n", \
    rotation.x, rotation.y, rotation.z);
}

void    print_sphere(t_obj obj)
{
    printf("SPHERE :\n");
    print_pos(obj.position);
    printf("    diameter: %lf\n", obj.diameter);
    print_color(obj.color);
    
}

void    print_plane(t_obj obj)
{
    printf("PLANE :\n");
    print_pos(obj.position);
    print_rotation(obj.rotation);
    print_color(obj.color);
}

void    print_cylinder(t_obj obj)
{
    printf("CYLINDER :\n");
    print_pos(obj.position);
    print_rotation(obj.rotation);
    printf("    diameter: %lf\n", obj.diameter);
    printf("    height: %lf\n", obj.height);
    print_color(obj.color);
}

void    print_ambient_light(t_alight light)
{
    if (!light.created)
        return ;
    printf("AMBIENT LIGHT :\n");
    printf("    brightness: %lf\n", light.brightness);
    print_color(light.color);
}

void    print_light(t_light light)
{
    if (!light.created)
        return ;
    printf("LIGHT :\n");
    print_pos(light.position);
    printf("    brightness: %lf\n", light.brightness);
    print_color(light.color);
}

void    print_camera(t_camera camera)
{
    if (!camera.created)
        return ;
    printf("CAMERA :\n");
    print_pos(camera.position);
    print_rotation(camera.direction);
    printf("    fov: %d\n", camera.fov);
}

void    print_objects(void)
{
    t_data      *data;
    t_obj_list  *obj;

    data = get_data();
    obj = data->objects;
    print_ambient_light(data->alight);
    print_light(data->light);
    print_camera(data->camera);
    while (obj)
    {
        if (obj->object.type == SPHERE)
            print_sphere(obj->object);
        else if (obj->object.type == PLANE)
            print_plane(obj->object);
        else if (obj->object.type == CYLINDER)
            print_cylinder(obj->object);
        obj = obj->next;
    }
}
