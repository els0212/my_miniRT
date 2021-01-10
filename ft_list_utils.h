#ifndef FT_LIST_UTILS_H
# define FT_LIST_UTILS_H
# include "minirt.h"

void		ft_add_last(t_object **list, t_object *obj);
void		ft_add_light_last(t_lht **list, t_lht *obj);
void		ft_add_camera_last(t_cam **list, t_cam *obj);
#endif
