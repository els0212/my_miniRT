#include "minirt.h"

int		ft_ins_plane(char **chunks, t_compo *compo, int size)
{
	t_object	*plane;
	t_vector	*vec;
	t_vector	*dir;
	t_color		*color;

	if (size != 4 || !(plane = ft_object_init(PLANE)))
		return (-1);
	if (!(vec = ft_make_vector(chunks[1])) ||
			!(dir = ft_make_vector(chunks[2])) ||
			!(color = ft_make_color(chunks[3])))
		return (-1);
	else if (dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1)
	{
		free(plane);
		free(vec);
		free(dir);
		free(color);
		return (-1);
	}
	plane->color = color;
	plane->dir = dir;
	plane->vec = vec;
	ft_add_last(&compo->objects, plane);
	printf("## processing plane\n  \
	r = %d, g = %d, b = %d\n\
	dir x = %lf, y = %lf, z = %lf\n\
	coordinates x = %lf, y = %lf, z = %lf\n",\
	color->red, color->green, color->blue,
	plane->dir->x, plane->dir->y, plane->dir->z,
	plane->vec->x, plane->vec->y, plane->vec->z);
	return (0);
}

int		ft_ins_square(char **chunks, t_compo *compo, int size)
{
	t_object	*square;
	t_vector	*vec;
	t_vector	*dir;
	t_color		*color;

	if (size != 5 || !(square = ft_object_init(SQUARE)))
		return (-1);
	if (!(vec = ft_make_vector(chunks[1])) ||
			!(dir = ft_make_vector(chunks[2])) ||
			!(color = ft_make_color(chunks[4])))
		return (-1);
	else if ((square->size = ft_atod(chunks[3])) <= 0 ||
			dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1)
	{
		free(square);
		free(vec);
		free(dir);
		free(color);
		return (-1);
	}
	square->color = color;
	square->dir = dir;
	square->vec = vec;
	ft_add_last(&compo->objects, square);
	printf("## processing square\n  \
	side size = %lf\nr = %d, g = %d, b = %d\n\
	dir x = %lf, y = %lf, z = %lf\n\
	coordinates x = %lf, y = %lf, z = %lf\n",\
	square->size, color->red, color->green, color->blue,
	square->dir->x, square->dir->y, square->dir->z,
	square->vec->x, square->vec->y, square->vec->z);
	return (0);
}

int		ft_ins_cylinder(char **chunks, t_compo *compo, int size)
{
	t_object	*cylinder;
	t_vector	*vec;
	t_vector	*dir;
	t_color		*color;

	if (size != 6 || !(cylinder = ft_object_init(CYLINDER)))
		return (-1);
	if (!(vec = ft_make_vector(chunks[1])) ||
			!(dir = ft_make_vector(chunks[2])) ||
			!(color = ft_make_color(chunks[5])))
		return (-1);
	else if ((cylinder->dia = ft_atod(chunks[3])) <= 0 ||
			(cylinder->height = ft_atod(chunks[4])) <= 0 ||
			dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1)
	{
		free(cylinder);
		free(vec);
		free(dir);
		free(color);
		return (-1);
	}
	cylinder->color = color;
	cylinder->dir = dir;
	cylinder->vec = vec;
	ft_add_last(&compo->objects, cylinder);
	printf("## processing cylinder\n  \
	dia = %lf, height = %lf\nr = %d, g = %d, b = %d\n\
	dir x = %lf, y = %lf, z = %lf\n\
	coordinates x = %lf, y = %lf, z = %lf\n",\
	cylinder->dia, cylinder->height, color->red, color->green, color->blue,
	cylinder->dir->x, cylinder->dir->y, cylinder->dir->z,
	cylinder->vec->x, cylinder->vec->y, cylinder->vec->z);
	return (0);
}

int		ft_ins_triangle(char **chunks, t_compo *compo, int size)
{
	t_object	*triangle;
	t_vector	*vec[3];
	t_color		*color;
	int			st;

	if (size != 5 || !(triangle = ft_object_init(TRIANGLE)))
		return (-1);
	else if (!(color = ft_make_color(chunks[4])))
		return (-1);
	st = 0;
	while (st < 3)
	{
		if (!(vec[st] = ft_make_vector(chunks[st + 1])))
			while (st >= 0)
				free(vec[st]);
		st++;
	}
	triangle->color = color;
	triangle->vec = vec[0];
	triangle->vec_second = vec[1];
	triangle->vec_third = vec[2];
	ft_add_last(&compo->objects, triangle);
	printf("## processing triangle\n  \
	r = %d, g = %d, b = %d\n\
	coordinates1 x = %lf, y = %lf, z = %lf\n\
	coordinates2 x = %lf, y = %lf, z = %lf\n\
	coordinates3 x = %lf, y = %lf, z = %lf\n",\
	color->red, color->green, color->blue,
	triangle->vec->x, triangle->vec->y, triangle->vec->z,
	triangle->vec_second->x, triangle->vec_second->y, triangle->vec_second->z,
	triangle->vec_third->x, triangle->vec_third->y, triangle->vec_third->z);
	return (0);
}
