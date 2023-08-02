#include "../../includes/minirt.h"

int     string_array_size(char **sa)
{
    int i;

    if (!sa)
        return (0);
    i = -1;
    while (sa[++i])
        ;
    return (i);
}

void    print_string_array(char **sa)
{
    int i;

    if (!sa)
        return ;
    i = -1;
    while (sa[++i])
        printf("%s\n", sa[i]);
}

void    free_string_array(char **sa)
{
    int i;

    if (!sa)
        return ;
    i = -1;
    while (sa[++i])
        free(sa[i]);
    free(sa);
    sa = NULL;
}

void    copy_string_array(char **dest, char **src)
{
    int i;

    if (!src)
        return ;
    i = -1; 
    while (src[++i])
        dest[i] = src[i];
    dest[i] = NULL;
}
