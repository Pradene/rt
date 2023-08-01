#include "../../includes/parsing.h"

v3  strtov3(char *s)
{
    v3      c;
    char    *tmp;
    char    **colors;

    c.r = 0.0;
    c.g = 0.0;
    c.b = 0.0;
    colors = ft_split(s, ',');
    if (!colors)
        return (c);
    if (string_array_size(colors) != 3)
        return (free_string_array(colors), c);
    c.r = strtofloat(colors[0], &tmp);
    c.g = strtofloat(colors[1], &tmp);
    c.b = strtofloat(colors[2], &tmp);
    free_string_array(colors);
    return (c);
}
