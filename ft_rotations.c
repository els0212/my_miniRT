t_vector	ft_rotate_x(t_vector now, double angle)
{
	t_vector	ret;

	ret.x = now.x;
	ret.y = cos(angle) * now.y - sin(angle) * z;
	ret.z = sin(angle) * now.y + cos(angle) * z;
	return (ret);
}

t_vector	ft_rotate_y(t_vector now, double angle)
{
	t_vector	ret;

	ret.x = cos(angle) * now.x + sin(angle) * z;
	ret.y = now.y;
	ret.z = -sin(angle) * now.x + cos(angle) * z;
	return (ret);
}

t_vector	ft_rotate_z(t_vector now, double angle)
{
	t_vector	ret;

	ret.x = cos(angle) * now.x - sin(angle) * y;
	ret.y = sin(angle) * now.x + cos(angle) * y;
	ret.z = now.z;
	return (ret);
}
