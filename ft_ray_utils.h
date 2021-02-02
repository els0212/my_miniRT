#ifndef FT_RAY_UTILS_H
# define FT_RAY_UTILS_H
# define RAYMAX 1000
# define EPSILON 0.0000001
# include "ft_vec_operations.h"
# include "ft_math_utils.h"
# include "ft_color_utils.h"

t_ray				*ft_ray_init(t_vector *origin, t_vector dir);
t_vector			ft_ray_at(t_ray ray, double d);
int					ft_ray_change_hit(t_ray *ray, int t, t_object *hit_obj);
t_ray				*ft_make_ray(t_res *res, t_cam *cam, int i, int j);
void				ft_free_ray(t_ray *ray);
#endif
