/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:35:12 by hyi               #+#    #+#             */
/*   Updated: 2021/01/08 18:42:22 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H

typedef struct		s_vector{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_color
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
}					t_color;

typedef struct		s_resolution
{
	int				x;
	int				y;
}					t_resolution;

typedef struct		s_camera
{
	t_vector		vec;
	t_vector		dir;
	double			fov;
}					t_camera;

typedef struct		s_object
{
	int				id;
	t_vector		vec;
	t_vector		vec_tri_2;
	t_vector		vec_tri_3;

#endif
