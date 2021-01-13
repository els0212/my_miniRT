#include "minirt.h"

double	ft_degree_to_radian(double degree)
{
	double	radian;

	radian = degree * ( PI / 180.0);
	return (radian);
}

t_vector	*ft_cross_product(t_vector a, t_vector b)
{
	t_vector	*ret;

	if (!(ret = (t_vector *)malloc(sizeof(t_vector))))
		return (0);
	ret->x = a.y * b.z - a.z * b.y;
	ret->y = a.z * b.x - b.x * a.z;
	ret->z = a.x * b.y - a.y * b.x;
	return (ret);
}

double	ft_dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
