#include "../../includes/minirt.h"

void	pixel_put(t_image *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void    trace(t_data *data, t_image *img)
{
    int     y;
    int     x;
    t_ray   ray;
    int32_t color;

    y = -1;
    ray.position = data->camera.position;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            ray.position = data->camera.position;
            ray.direction.x = (((x + 0.5) / WIDTH) * 2.0 - 1.0) * ASPECT_RATIO * tan(radian(data->camera.fov / 2));
            ray.direction.y = (((HEIGHT - (y + 0.5)) / HEIGHT) * 2.0 - 1.0) * tan(radian(data->camera.fov / 2));
            ray.direction.z = -data->camera.direction.z;
            ray.direction = normalize(ray.direction);
            color = intersect(ray);
            pixel_put(img, x, y, color);
        }
    }
}

int update(t_data *data)
{
    if (!data->win)
        return (1);
    trace(data, &data->img);
    mlx_put_image_to_window(data->id, data->win, data->img.image, 0, 0);
    return (0);
}

void    render()
{
    t_data  *data;

    data = get_data();
    mlx_loop_hook(data->id, &update, data);
	mlx_hook(data->win, 2, 1L << 0, &key, data);
	mlx_hook(data->win, 17, 0, &free_data, data);
    mlx_loop(data->id);
}