#include "ft_parse_rt_1.h"

int		ft_ins_resolution(char **chunks, t_compo *compo, int size)
{
	t_res	*resolution;
	int		x;
	int		y;

	if (size != 3)
		return (ft_error("resolution has wrong number of attributes"));
	else if (compo->resolution)
		return (ft_error("greater than one resolution is included"));
	else if (!(resolution = (t_res *)malloc(sizeof(t_res))))
		return (ft_error("resolution memory allocation is failed"));
	x = ft_atoi(chunks[1]);
	y = ft_atoi(chunks[2]);
	if (x <= 0 || y <= 0)
	{
		free(resolution);
		return (ft_error("x or y is less than or equal to 0"));
	}
	resolution->x = x;
	resolution->y = y;
	resolution->ratio = (double)x / (double)y;
	compo->resolution = resolution;
	return (0);
}

int		ft_ins_ambient(char **chunks, t_compo *compo, int size)
{
	t_amb	*ambient;
	t_color	*color;

	if (size != 3)
		return (ft_error("ambient has wrong number of attributes"));
	else if (compo->ambient)
		return (ft_error("greater than one ambient is included"));
	else if (!(ambient = (t_amb *)malloc(sizeof(t_amb))))
		return (ft_error("ambient memory allocation is failed"));
	else if (ft_atod(chunks[1]) < 0 || ft_atod(chunks[1]) > 1)
	{
		free(ambient);
		return (ft_error("the range of ambient ratio is wrong"));
	}
	if (!(color = ft_chunks_to_color(chunks[2])))
		return (ft_error("ambient color is wrong"));
	ambient->ratio = ft_atod(chunks[1]);
	ambient->color = color;
	compo->ambient = ambient;
	return (0);
}

int		ft_ins_camera(char **chunks, t_compo *compo, int size)
{
	t_vector	*vec;
	t_vector	*dir;

	if (size != 4)
		return (ft_error("camera has wrong number of attributes"));
	else if (!(vec = ft_chunks_to_vec(chunks[1])))
		return (ft_error("camera coordinte is wrong"));
	else if (!(dir = ft_chunks_to_vec(chunks[2])))
	{
		free(vec);
		return (ft_error("map errror : camera color is wrong"));
	}
	else if (ft_camera_init(compo, vec, dir, ft_atod(chunks[3])))
	{
		free(vec);
		free(dir);
		return (ft_error("camera init is failed"));
	}
	return (0);
}

int		ft_ins_light(char **chunks, t_compo *compo, int size)
{
	t_vector	*vec;
	t_color		*color;

	if (size != 4)
		return (ft_error("light has wrong number of attributes"));
	else if (!(vec = ft_chunks_to_vec(chunks[1])))
		return (ft_error("light coordinte is wrong"));
	else if (!(color = ft_chunks_to_color(chunks[3])))
	{
		free(vec);
		return (ft_error("map errror : light color is wrong"));
	}
	else if (ft_light_init(compo, color, vec, ft_atod(chunks[2])))
	{
		free(vec);
		free(color);
		return (ft_error("light init is failed"));
	}
	return (0);
}

int		ft_ins_sphere(char **chunks, t_compo *compo, int size)
{
	t_vector	*vec;
	t_color		*color;

	if (size != 4)
		return (ft_error("sphere has wrong number of attributes"));
	else if (!(vec = ft_chunks_to_vec(chunks[1])))
		return (ft_error("sphere coordinte is wrong"));
	if (!(color = ft_chunks_to_color(chunks[3])))
	{
		free(vec);
		return (ft_error("map errror : sphere color is wrong"));
	}
	if (ft_sphere_init(compo, color, vec, ft_atod(chunks[2])))
	{
		free(vec);
		free(color);
		return (ft_error("sphere init is failed"));
	}
	return (0);
}
