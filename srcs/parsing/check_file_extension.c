#include "../../includes/minirt.h"

int check_extension(char *extension)
{
    int i;

    if (extension[0] != '.')
        return (0);
    i = 0;
    while (extension[++i])
    {
        if (!isalnum(extension[i]))
            return (0);
    }
    return (1);
}

int check_file_extension(char *path, char *extension)
{
    if (!check_extension(extension))
        return (0);
    if (strstr(path, extension) == &path[strlen(path) - strlen(extension)])
        return (1);
    return (0);
}