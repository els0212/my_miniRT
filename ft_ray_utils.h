#ifndef FT_RAY_UTILS_H
# define FT_RAY_UTILS_H
# define RAYMAX 1000
# define EPSILON 0.0000001
# include "ft_struct.h"
# include "ft_libft.h"
# include "ft_vec_operations.h"
# include "ft_math_utils.h"
# include "ft_color_utils.h"
t_ray				*ft_ray_init(t_vector *origin, t_vector dir);
t_vector			ft_ray_at(t_ray ray, double d);
t_vector			*ft_get_normal(t_vector hit_point, t_object obj);
int					ft_ray_change_hit(t_ray *ray, int t, t_object *hit_obj);
int					ft_ray_hit_sphere(t_object *sphere, t_ray *ray, double t);
int					ft_ray_hit_plane(t_object *plane, t_ray *ray, int t);
int					ft_ray_hit_square(t_object *square, t_ray *ray);
int					ft_triangle_inside_outside(t_vector p, t_vector a, t_vector b, t_vector n);
int					ft_ray_hit_triangle(t_object *triangle, t_ray *ray, int t);
int					ft_ray_hit_cylinder(t_object *cylinder, t_ray *ray);
t_color				*ft_ray_color(t_ray *ray, t_object *obj);
int					ft_chk_intersect(t_object *obj, t_ray *ray);
#endif
