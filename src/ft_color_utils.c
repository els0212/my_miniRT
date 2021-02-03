/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:37:40 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:37:41 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color_utils.h"

t_color			ft_color_init(int r, int g, int b)
{
	t_color	color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

t_color			*ft_color_cpy(t_color *c1, t_color c2)
{
	c1->red = c2.red;
	c1->green = c2.green;
	c1->blue = c2.blue;
	return (c1);
}

t_color			*ft_color_mult(t_color *c1, t_color c2)
{
	c1->red = fmin((c1->red * c2.red) / 255, 255);
	c1->green = fmin((c1->green * c2.green) / 255, 255);
	c1->blue = fmin((c1->blue * c2.blue) / 255, 255);
	return (c1);
}

t_color			ft_color_mult_const(t_color *c1, double ratio)
{
	t_color	ret;

	ret.red = fmin(c1->red * ratio, 255);
	ret.green = fmin(c1->green * ratio, 255);
	ret.blue = fmin(c1->blue * ratio, 255);
	return (ret);
}

t_color			ft_color_add(t_color c1, t_color c2)
{
	t_color	ret;

	ret.red = fmin(c1.red + c2.red, 255);
	ret.green = fmin(c1.green + c2.green, 255);
	ret.blue = fmin(c1.blue + c2.blue, 255);
	return (ret);
}
