/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:35:12 by hyi               #+#    #+#             */
/*   Updated: 2021/01/07 23:35:29 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H
typedef struct{
	double			x;
	double			y;
	double			z;
}					t_axis;

typedef struct{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
}					t_color;

typedef struct{
	int				x;
	int				y;
}					t_resolution;

typedef struct{
	double			ratio;
	t_color			color;
}					t_ambient;

typedef struct{
	t_axis			axis;
	t_axis			norm;
	int				degree;
}	t_camera;

typedef struct{
	t_axis			axis;
	double			ratio;
	t_color			color;
}	t_light;

typedef struct{
	t_axis			axis;
	double			dia;
	t_color			color;
}	t_sphere;

typedef struct{
	t_axis			axis;
	t_axis			norm;
	double			size;
	t_color			color;
}	t_plane;

typedef struct{
	t_axis			axis;
	t_axis			norm;
	double			dia;
	double			height;
	t_color			color;
}	t_cylinder;

typedef struct{
	t_axis			first;
	t_axis			second;
	t_axis			third;
	t_color			color;
}	t_triangle;
#endif
