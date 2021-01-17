/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_miniRT.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:13:18 by hyi               #+#    #+#             */
/*   Updated: 2021/01/17 14:58:45 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define BUFFER_SIZE 1024
# define PI 3.1415926535
# define ESCAPE 53
# define KEYPRESS 2
# define KEYPRESSMASK (1L<<0)
# define DESTROYNOTIFY 17
# define STRUCTURENOTIFYMASK (1L<<17)
# define RAYMAX 1000
# define EPSILON 0.000001
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "mlx/mlx.h"

/*
** Header for mandatory part structs (R, A, c, l, pl, sp, sq, cy, tr)
*/
# include "ft_struct.h"
# include "ft_list_utils.h"
# include "ft_mlx_utils.h"
#include <stdio.h>

/*
** ft_split.c
*/
int					ft_iscomma(char c);
char				**ft_split(const char *s, int (*ft_is)(char c));
void				ft_free(char **ret, int ret_st);
int					ft_cnt_lines(const char *s, int (*ft_is)(char c));
int					ft_next_idx(const char *s, int (*ft_is)(char c), int st);

/*
** ft_libft.c
*/
int					ft_strncmp(const char *s1, const char *s2, int len);
char				*ft_strrchr(const char *s, int c);
size_t				ft_strlen(const char *s);
char				*ft_substr(const char *s, unsigned int start, size_t len);
int					ft_isspace(char c);

/*
** get_next_line_utils.c
*/
int					ft_memset(char **line, size_t size);
int					ft_get_new_line_idx(char *buf);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				ft_resize_and_copy(char **line, char *buf, int st, int ed);
char				*ft_strdup(char *str);
/*
** get_next_line.c
*/
int					ft_get_len(char *str);
int					ft_while_loop(char **line, char *buf, char **buf_ref);
int					ft_proc_buf_ref(char **line, char **buf_ref);
int					get_next_line(int fd, char **line);
/*
** ft_utils.c 
*/
int					ft_get_size(char **chunks);
int					ft_get_sign(const char *nptr, int *sign);
int					ft_atoi(const char *nptr);
double				ft_atod(const char *nptr);
/*
** ft_parse_rt_1.c 
*/
int					ft_ins_resolution(char **chunks, t_compo *compo, int size);
int					ft_ins_ambient(char **chunks, t_compo *compo, int size);
int					ft_ins_camera(char **chunks, t_compo *compo, int size);
int					ft_ins_light(char **chunks, t_compo *compo, int size);
int					ft_ins_sphere(char **chunks, t_compo *compo, int size);
/*
** ft_parse_rt_2.c 
*/
int					ft_ins_plane(char **chunks, t_compo *compo, int size);
int					ft_ins_square(char **chunks, t_compo *compo, int size);
int					ft_ins_cylinder(char **chunks, t_compo *compo, int size);
int					ft_ins_triangle(char **chunks, t_compo *compo, int size);
/*
** ft_math_utils.c 
*/
double				ft_degree_to_radian(double degree);
t_vector			*ft_cross_product(t_vector a, t_vector b);
double				ft_dot_product(t_vector a, t_vector b);
double				ft_get_dist(t_vector a, t_vector b);
/*
** ft_vec_operations.c 
*/
void				ft_vec_cpy(t_vector *vec1, t_vector vec2);
t_vector			*ft_vec_dup(t_vector src);
t_vector			ft_vec_add(t_vector vec1, t_vector vec2);
t_vector			ft_vec_sub(t_vector vec1, t_vector vec2);
t_vector			ft_vec_product_const(t_vector vec, double d);
t_vector			ft_vec_div_const(t_vector vec, double d);
/*
** ft_ray_utils.c 
*/
t_ray				*ft_ray_init(t_vector *origin, t_vector dir);
t_vector			ft_ray_at(t_ray ray, double d);
void		ft_square_t_range(double *min, double *max, double origin, double dir);
int			ft_ray_hit_square(t_object *square, t_ray *ray);
int					ft_ray_hit_sphere(t_object *sphere, t_ray *ray, int t);
int					ft_ray_hit_plane(t_object *plane, t_ray *ray, int t);
t_color				*ft_ray_color(t_ray *ray, t_object *obj);
#endif
