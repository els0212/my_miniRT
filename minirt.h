/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_miniRT.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:13:18 by hyi               #+#    #+#             */
/*   Updated: 2021/01/10 00:11:44 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
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
# define BUFFER_SIZE 1024
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
#endif
