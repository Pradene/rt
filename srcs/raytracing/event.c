#include "../../includes/minirt.h"

int	key(int key, t_data *data)
{
    (void)data;
	// printf("%d\n", key);
	if (key == 65307)
		free_data();
	return (0);
}
