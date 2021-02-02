#ifndef FT_PARSE_UTILS_2_H
# define FT_PARSE_UTILS_2_H
# include "ft_color_utils.h"
# include "ft_list_utils.h"
# include "ft_ray_utils.h"

int			ft_camera_init(t_compo *compo, t_vector *vec,
		t_vector *dir, double angle);
int			ft_light_init(t_compo *compo, t_color *color,
		t_vector *vec, double ratio);
char		**ft_parse_args(char *str);
t_vector	*ft_chunks_to_vec(char *str);
t_color		*ft_chunks_to_color(char *str);
#endif
