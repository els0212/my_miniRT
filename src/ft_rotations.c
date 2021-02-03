/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:40:13 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:40:13 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rotations.h"

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
