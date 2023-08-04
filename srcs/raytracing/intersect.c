#include "../../includes/minirt.h"

int get_color(t_obj obj, t_ray ray, float t)
{
    t_data  *data;
    float   ratio;
    v3      dir;
    v3      hp;
    v3      c;

    data = get_data();
    hp = ray.position - obj.position + ray.direction * t;
    dir = normalize(hp - data->light.position);
    ratio = max(0.0, dot(normalize(hp), -dir));
    c = obj.color / 255 * min(1.0, ratio + data->alight.brightness);
    return (rgba_to_color(c.r, c.g, c.b, 1.0));
}

float   ray_sphere_intersection(t_obj obj, t_ray ray)
{
    float   a;
    float   b;
    float   c;
    float   t0;
    float   t1;

    a = dot(ray.direction, ray.direction);
    b = 2.0 * dot(ray.position - obj.position, ray.direction);
    c = dot(ray.position - obj.position, ray.position - obj.position) \
    - (obj.diameter / 2) * (obj.diameter / 2);
    if (b * b - 4.0 * a * c < 0.0)
        return (-1.0);
    t0 = (-b - sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
    t1 = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
    if (t0 < 0 && t1 > 0)
        return (-1.0);
    return (t0);
}

int intersect(t_ray ray)
{
    t_data      *data;
    t_obj_list  *tmp;
    int         color;
    float       tdistance;
    float       distance;

    color = 0;
    data = get_data();
    tmp = data->objects;
    distance = FLT_MAX;
    while (tmp)
    {
        if (tmp->object.type == SPHERE)
        {
            tdistance = ray_sphere_intersection(tmp->object, ray);
            if (tdistance > 0 && tdistance < distance)
            {
                distance = tdistance;
                color = get_color(tmp->object, ray, distance);
            }
        }
        tmp = tmp->next;
    }
    return (color);
}
