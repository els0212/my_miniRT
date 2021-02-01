#ifndef FT_SHADER_H
# define FT_SHADER_H
# include "ft_struct.h"
# include "ft_color_utils.h"
# include "ft_vec_operations.h"
# include "ft_math_utils.h"
# include "ft_ray_utils.h"
t_color	ft_specular(t_lht *now, t_ray ray);
t_color	ft_get_light_color(t_lht *now, t_object *objs, t_ray ray);
t_color	ft_shader(t_lht *lht, t_object *objs, t_ray ray);
#endif
