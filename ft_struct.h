/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:35:12 by hyi               #+#    #+#             */
/*   Updated: 2021/02/01 19:01:59 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H
# include <math.h>
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

typedef struct s_object	t_object;
typedef struct			s_ray{
	t_vector			*origin;
	t_vector			*dir;
	t_vector			*hit_point;
	t_vector			*hit_norm;
	t_object			*hit_obj;
	int					ray_hit;
}						t_ray;

typedef struct			s_color
{
	int					red;
	int					green;
	int					blue;
}						t_color;

typedef struct			s_resolution
{
	int					x;
	int					y;
	double				ratio;
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
	t_vector			*u;
	t_vector			*v;
	double				fov;
	int					order;
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
** dia						: Sphere, Square, Cylinder
** height					: Cylinder
** direction				: Plane, Square, Cylinder
**							: in range [-1, 1]
** size						: Square
*/
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
	int					save;
}						t_compo;

t_compo					*ft_compo_init();
t_object				*ft_object_init(int id);
int			ft_camera_init(t_compo *compo, t_vector *vec, t_vector *dir, double angle);
int			ft_light_init(t_compo *compo, t_color *color, t_vector *vec, double ratio);
int			ft_sphere_init(t_compo *compo, t_color *color, t_vector *vec, double dia);
int			ft_plane_init(t_compo *compo, t_color *color, t_vector *vec, t_vector *dir);
t_object		*ft_square_init(t_compo *compo, t_color *color, t_vector *vec, t_vector *dir);
t_object		*ft_cylinder_init(t_compo *compo, t_color *color, t_vector *vec, t_vector *dir);
int			ft_triangle_init(t_compo *compo, t_color *color, char **chunks);
char		**ft_parse_args(char *str);
t_vector				ft_vector_init(double x, double y, double z);
t_vector				*ft_chunks_to_vec(char *str);
t_color					*ft_chunks_to_color(char *str);
t_vector				ft_normalize(t_vector vec);
#endif
