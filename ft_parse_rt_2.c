#include "minirt.h"

int		ft_ins_plane(char **chunks, t_compo *compo, int size)
{
	t_vector	*vec;
	t_vector	*dir;
	t_color		*color;

	if (size != 4)
		return (ft_error("plane has wrong number of attributes"));
	else if (!(vec = ft_make_vector(chunks[1])))
		return (ft_error("plane coordinate is wrong"));
	else if (!(color = ft_make_color(chunks[3])))
		return (ft_error("plane color is wrong"));
	else if (ft_plane_init(compo, color, vec,
				(dir = ft_make_vector(chunks[2]))))
	{
		free(vec);
		free(dir);
		free(color);
		return (ft_error("plane init is failed"));
	}
	return (0);
}

int		ft_ins_square(char **chunks, t_compo *compo, int size)
{
	t_object	*square;
	t_vector	*vec;
	t_vector	*dir;
	t_color		*color;
	double		square_size;

	if (size != 5)
		return (ft_error("square has wrong number of attributes"));
	else if (!(vec = ft_make_vector(chunks[1])))
		return (ft_error("square coordinate is wrong"));
	else if (!(color = ft_make_color(chunks[4])))
		return (ft_error("square color is wrong"));
	else if ((square_size = ft_atod(chunks[3])) <= 0)
		return (ft_error("square size is less than or equal to 0"));
	else if (!(square = ft_square_init(compo, color, vec,
					(dir = ft_make_vector(chunks[2])))))
	{
		free(vec);
		free(dir);
		free(color);
		return (ft_error("square init is failed"));
	}
	square->size = square_size;
	return (0);
}

int		ft_ins_cylinder(char **chunks, t_compo *compo, int size)
{
	t_object	*cylinder;
	t_vector	*vec;
	t_vector	*dir;
	t_color		*color;

	if (size != 6)
		return (ft_error("cylinder has wrong number of attributes"));
	if (!(vec = ft_make_vector(chunks[1])))
		return (ft_error("cylinder coordinate is wrong"));
	else if (!(color = ft_make_color(chunks[5])))
		return (ft_error("cylinder color is wrong"));
	else if (ft_atod(chunks[3]) <= 0 || ft_atod(chunks[4]) <= 0)
		return (ft_error("cylinder height or diameter is wrong"));
	else if (!(cylinder = ft_cylinder_init(compo, color, vec,
					(dir = ft_make_vector(chunks[2])))))
	{
		free(vec);
		free(dir);
		free(color);
		return (ft_error("cylinder init is failed"));
	}
	cylinder->dia = ft_atod(chunks[3]);
	cylinder->height = ft_atod(chunks[4]);
	return (0);
}

int		ft_ins_triangle(char **chunks, t_compo *compo, int size)
{
	t_color		*color;

	if (size != 5)
		return (ft_error("triangle has wrong number of attributes"));
	else if (!(color = ft_make_color(chunks[4])))
		return (ft_error("triangle color is wrong"));
	else if (ft_triangle_init(compo, color, chunks))
	{
		free(color);
		return (ft_error("triangle init is failed"));
	}
	return (0);
}
