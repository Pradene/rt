#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

# include <stdio.h>
# include <stdlib.h>

# include <string.h>

# include <math.h>

# include <limits.h>
# include <float.h>

# include <ctype.h>

# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>


# define HEIGHT 800
# define WIDTH 1200
# define PI 3.14159265359
# define ASPECT_RATIO (float)WIDTH / (float)HEIGHT

typedef float v3 __attribute__((ext_vector_type(3)));

typedef enum    e_obj_type
{
    ERROR,
    AMBIENT_LIGHT,
    CAMERA,
    LIGHT,
    SPHERE,
    PLANE,
    CYLINDER
}   t_obj_type;

typedef struct  s_obj
{
    t_obj_type  type;
    v3          position;
    v3          rotation;
    v3          color;
    float       diameter;
    float       height;
    float       width;
}   t_obj;

typedef struct  s_obj_list
{
    t_obj               object;
    struct s_obj_list   *next;
}   t_obj_list;

typedef struct  s_ray
{
    v3  position;
    v3  direction;
}   t_ray;

typedef struct  s_camera
{
    int created;
    v3  position;
    v3  direction;
    int fov;
}   t_camera;

typedef struct  s_light
{
    int     created;
    v3      position;
    v3      color;
    float   brightness;
}   t_light;

typedef struct  s_alight
{
    int     created;
    v3      color;
    float   brightness;
}   t_alight;

typedef struct s_image
{
	void	*image;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

typedef struct  s_data
{
    t_obj_list  *objects;
    t_camera    camera;
    t_light     light;
    t_alight    alight;
    void        *id;
    void        *win;
    t_image     img;
}   t_data;

t_data  *get_data();
int     free_data();

// PARSING

char    *gnl(int fd);

int     check_color(v3 color);
int     check_brightness(float brightness);
int     check_fov(int fov);
int     check_direction(v3 direction);

void    free_objects(t_obj_list **lst);
void    add_objects(t_obj_list **lst, t_obj_list *new);
void    print_objects(void);

int     string_array_size(char **sa);
void    print_string_array(char **sa);
void    free_string_array(char **sa);
void    copy_string_array(char **dest, char **src);

v3      strtov3(char *s);

float   strtofloat(char *s, char **end);

int     check_file_extension(char *path, char *extension);

void    create_objs(char **sa);

void    parsing(char *path);


// MATHS

float   max(float n0, float n1);
float   min(float n0, float n1);


float   clamp(float v, float min, float max);
float   dot(v3 p, v3 q);
v3      normalize(v3 vec);
float   radian(float angle);


// RENDER

int     rgba_to_color(float r, float g, float b, float a);

int	    key(int key, t_data *data);

int     intersect(t_ray ray);

void    render(void);
void    renderer(char *name);

#endif