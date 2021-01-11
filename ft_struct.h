/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:35:12 by hyi               #+#    #+#             */
/*   Updated: 2021/01/10 13:55:38 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H
# define RESOLUTION 1
# define AMBIENT 2
# define CAMERA 3
# define LIGHT 4
# define SPHERE 5
# define PLANE 6
# define SQUARE 7
# define CYLINDER 8
# define TRIANGLE 9

typedef struct			s_vector{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct			s_color
{
	unsigned int		red;
	unsigned int		green;
	unsigned int		blue;
}						t_color;

typedef struct			s_resolution
{
	int					x;
	int					y;
}						t_res;

typedef struct			s_ambient
{
	double				ratio;
	t_color				*color;
}						t_amb;

typedef struct s_camera	t_cam;
struct					s_camera
{
	t_vector			*vec;
	t_vector			*dir;
	double				fov;
	double				focal_len;
	t_vector			left_up;
	t_vector			left_down;
	t_vector			right_up;
	t_vector			right_down;
	t_cam				*next;
};

typedef struct s_light	t_lht;
struct					s_light
{
	t_vector			*vec;
	double				ratio;
	t_color				*color;
	t_lht				*next;

};

/*
** id, vector, color		: Common attributes
** color					: in range [0, 255]
** vec_second, vec_third	: Triangle
** dia						: Sphere, Square, Cylinde
** height					: Cylinder
** direction				: Plane, Square, Cylinder
**							: in range [-1, 1]
** size						: Square
*/
typedef struct s_object	t_object;
struct					s_object
{
	int					id;
	t_vector			*vec;
	t_color				*color;

	t_vector			*vec_second;
	t_vector			*vec_third;

	double				dia;

	double				height;

	t_vector			*dir;

	double				size;
	t_object			*next;
};

typedef struct			s_component
{
	t_res				*resolution;
	t_amb				*ambient;
	t_cam				*camera;
	t_lht				*light;
	t_object			*objects;
}						t_compo;

t_compo					*ft_compo_init();
t_object				*ft_object_init(int id);
t_vector				*ft_make_vector(char *str);
t_color					*ft_make_color(char *str);
char					**ft_parse_args(char *str);
#endif
