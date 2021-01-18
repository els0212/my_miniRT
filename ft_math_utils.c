#include "minirt.h"

double	ft_degree_to_radian(double degree)
{
	double	radian;

	radian = degree * ( PI / 180.0);
	return (radian);
}

t_vector	ft_cross_product(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - b.x * a.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

double	ft_dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	ft_get_dist(t_vector a, t_vector b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)));}
