/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:38:55 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:38:55 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse_utils_1.h"

int			ft_sphere_init(t_compo *compo, t_color *color,
		t_vector *vec, double dia)
{
	t_object	*sphere;

	if (dia <= 0)
		return (ft_error("sphere diameter is less than or equals to 0"));
	else if (!(sphere = ft_object_init(SPHERE)))
		return (ft_error("sphere memory allocation is failed"));
	sphere->dia = dia;
	sphere->color = color;
	sphere->vec = vec;
	ft_add_last(&compo->objects, sphere);
	return (0);
}

int			ft_plane_init(t_compo *compo, t_color *color,
		t_vector *vec, t_vector *dir)
{
	t_object	*plane;

	if (dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1)
		return (ft_error("a range of plane direction is wrong"));
	else if (!(plane = ft_object_init(PLANE)))
		return (ft_error("plane memory allocation is failed"));
	plane->color = color;
	plane->dir = dir;
	plane->vec = vec;
	ft_add_last(&compo->objects, plane);
	return (0);
}

t_object	*ft_square_init(t_compo *compo, t_color *color,
		t_vector *vec, t_vector *dir)
{
	t_object	*square;

	if (dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1)
	{
		ft_error("a range of square direction is wrong");
		return (0);
	}
	else if (!(square = ft_object_init(SQUARE)))
	{
		ft_error("square memory allocation is failed");
		return (0);
	}
	square->color = color;
	square->dir = dir;
	square->vec = vec;
	ft_add_last(&compo->objects, square);
	return (square);
}

t_object	*ft_cylinder_init(t_compo *compo, t_color *color,
		t_vector *vec, t_vector *dir)
{
	t_object	*cylinder;

	if (dir->x > 1 || dir->x < -1 || dir->y > 1 || dir->y < -1 ||
			dir->z > 1 || dir->z < -1)
	{
		ft_error("a range of cylinder direction is wrong");
		return (0);
	}
	else if (!(cylinder = ft_object_init(CYLINDER)))
	{
		ft_error("cylinder memory allocation is failed");
		return (0);
	}
	cylinder->color = color;
	cylinder->dir = dir;
	cylinder->vec = vec;
	ft_add_last(&compo->objects, cylinder);
	return (cylinder);
}

int			ft_triangle_init(t_compo *compo, t_color *color, char **chunks)
{
	t_object	*triangle;
	t_vector	*vec[3];
	int			st;

	st = 0;
	if (!(triangle = ft_object_init(TRIANGLE)))
		return (ft_error("triangle memory allocation is failed"));
	while (st < 3)
	{
		if (!(vec[st] = ft_chunks_to_vec(chunks[st + 1])))
		{
			while (st >= 0)
				free(vec[st]);
			free(triangle);
			return (ft_error("triangle coordinate is wrong"));
		}
		st++;
	}
	triangle->color = color;
	triangle->vec = vec[0];
	triangle->vec_second = vec[1];
	triangle->vec_third = vec[2];
	ft_add_last(&compo->objects, triangle);
	return (0);
}
