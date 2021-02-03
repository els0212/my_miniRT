/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:41:06 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:41:07 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_struct.h"

t_compo		*ft_compo_init(void)
{
	t_compo		*ret;

	if (!(ret = (t_compo *)malloc(sizeof(t_compo))))
		return (0);
	ret->resolution = 0;
	ret->ambient = 0;
	ret->camera = 0;
	ret->light = 0;
	ret->objects = 0;
	ret->save = 0;
	return (ret);
}

t_object	*ft_object_init(int id)
{
	t_object	*ret;

	if (!(ret = (t_object *)malloc(sizeof(t_object))))
		return (0);
	ret->id = id;
	ret->vec = 0;
	ret->color = 0;
	ret->vec_second = 0;
	ret->vec_third = 0;
	ret->dia = 0;
	ret->height = 0;
	ret->dir = 0;
	ret->size = 0;
	ret->next = 0;
	return (ret);
}

t_vector	ft_vector_init(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vector	ft_normalize(t_vector vec)
{
	double	size;

	size = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x /= size;
	vec.y /= size;
	vec.z /= size;
	return (vec);
}

void		ft_vec_cpy(t_vector *vec1, t_vector vec2)
{
	vec1->x = vec2.x;
	vec1->y = vec2.y;
	vec1->z = vec2.z;
}
