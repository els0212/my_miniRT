#ifndef FT_PARSE_UTILS_1_H
# define FT_PARSE_UTILS_1_H
# include "ft_parse_utils_2.h"
int			ft_sphere_init(t_compo *compo, t_color *color, t_vector *vec, double dia);
int			ft_plane_init(t_compo *compo, t_color *color, t_vector *vec, t_vector *dir);
t_object	*ft_square_init(t_compo *compo, t_color *color, t_vector *vec, t_vector *dir);
t_object	*ft_cylinder_init(t_compo *compo, t_color *color, t_vector *vec, t_vector *dir);
int			ft_triangle_init(t_compo *compo, t_color *color, char **chunks);
#endif
