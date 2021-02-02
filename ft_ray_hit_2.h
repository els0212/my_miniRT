#ifndef FT_RAY_HIT_2_H
# define FT_RAY_HIT_2_H
# include "ft_ray_hit_1.h"

t_vector			*ft_get_normal(t_vector hit_point, t_object obj);
int					ft_ray_hit_cylinder(t_object *cylinder, t_ray *ray);
int					ft_chk_intersect(t_object *obj, t_ray *ray);
t_color				*ft_ray_color(t_ray *ray, t_object *obj);
#endif
