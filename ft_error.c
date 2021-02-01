#include "minirt.h"

int	ft_error(char *errmsg)
{
	write(2, "Error\n", 6);
	write(2, errmsg, ft_strlen(errmsg));
	write(2, "\n", 1);
	return (-1);
}
