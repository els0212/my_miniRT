#include "minirt.h"
t_vector	ft_rotate_x(t_vector now, double angle)
{
	t_vector	ret;

	ret.x = now.x;
	ret.y = cos(angle) * now.y - sin(angle) * now.z;
	ret.z = sin(angle) * now.y + cos(angle) * now.z;
	return (ret);
}

t_vector	ft_rotate_y(t_vector now, double angle)
{
	t_vector	ret;

	ret.x = cos(angle) * now.x + sin(angle) * now.z;
	ret.y = now.y;
	ret.z = -sin(angle) * now.x + cos(angle) * now.z;
	return (ret);
}

t_vector	ft_rotate_z(t_vector now, double angle)
{
	t_vector	ret;

	ret.x = cos(angle) * now.x - sin(angle) * now.y;
	ret.y = sin(angle) * now.x + cos(angle) * now.y;
	ret.z = now.z;
	return (ret);
}
