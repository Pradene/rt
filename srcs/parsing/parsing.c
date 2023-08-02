#include "../../includes/minirt.h"

char    **read_file(int fd)
{
    int     i;
    char    *line;
    char    **tmp;
    char    **file;

    i = -1;
    file = NULL;
    line = gnl(fd);
    if (!line)
        return (NULL);
    while (line)
    {
        tmp = NULL;
        line[strlen(line) - 1] = '\0';
        tmp = malloc(sizeof(char *) * ((++i + 1) + 1));
        if (!tmp)
            return (free_string_array(file), free(line), NULL);
        copy_string_array(tmp, file);
        free(file);
        tmp[i] = line;
        tmp[i + 1] = NULL;
        file = tmp;
        line = gnl(fd);
    }
    return (file);
}

void    parsing(char *pathname)
{
    int     fd;
    char    **file;

    if (!check_file_extension(pathname, ".rt"))
        return ;
    fd = open(pathname, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: invald file\n");
        return ;
    }
    file = read_file(fd);
    // print_string_array(file);
    create_objs(file);
    free_string_array(file);
    print_objects();
    close(fd);
}
