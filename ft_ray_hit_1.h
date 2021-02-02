#ifndef FT_RAY_HIT_1_H
# define FT_RAY_HIT_1_H
# include "ft_ray_hit_2.h"
int					ft_ray_hit_sphere(t_object *sphere, t_ray *ray, double t);
int					ft_ray_hit_plane(t_object *plane, t_ray *ray, int t);
int					ft_ray_hit_square(t_object *square, t_ray *ray);
int					ft_triangle_inside_outside(t_vector p, t_vector a, t_vector b, t_vector n);
int					ft_ray_hit_triangle(t_object *triangle, t_ray *ray, int t);
#endif
