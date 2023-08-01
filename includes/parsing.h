#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>

# include <string.h>

# include <ctype.h>

# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef float v3 __attribute__((ext_vector_type(3)));

typedef enum    e_obj_type
{
    ERROR,
    LIGHT,
    CAMERA,
    AMBIENT_LIGHT,
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

typedef struct  s_data
{
    t_obj_list  *objects;
    t_camera    camera;
    t_light     light;
    t_alight    alight;
}   t_data;

t_data  *get_data();

char    *gnl(int fd);

void    free_objects(t_obj_list **lst);
void    add_objects(t_obj_list **lst, t_obj_list *new);

int     string_array_size(char **sa);
void    print_string_array(char **sa);
void    free_string_array(char **sa);
void    copy_string_array(char **dest, char **src);

v3      strtov3(char *s);

float   strtofloat(char *s, char **end);

int     check_file_extension(char *path, char *extension);

void    create_objs(char **sa);

void    parsing(char *path);

#endif