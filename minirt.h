/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_miniRT.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:13:18 by hyi               #+#    #+#             */
/*   Updated: 2021/01/07 23:31:32 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "mlx/mlx.h"
# define BUFFER_SIZE 1024
#include <stdio.h>

typedef struct{
	double			x;
	double			y;
	double			z;
}					t_axis;

typedef struct{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
}					t_color;

typedef struct{
	int				x;
	int				y;
}					t_resolution;

typedef struct{
	double			ratio;
	t_color			color;
}					t_ambient;

typedef struct{
	t_axis			axis;
	t_axis			norm;
	int				degree;
}	t_camera;

typedef struct{
	t_axis			axis;
	double			ratio;
	t_color			color;
}	t_light;

typedef struct{
	t_axis			axis;
	double			dia;
	t_color			color;
}	t_sphere;

typedef struct{
	t_axis			axis;
	t_axis			norm;
	double			size;
	t_color			color;
}	t_plane;

typedef struct{
	t_axis			axis;
	t_axis			norm;
	double			dia;
	double			height;
	t_color			color;
}	t_cylinder;

typedef struct{
	t_axis			first;
	t_axis			second;
	t_axis			third;
	t_color			color;
}	t_triangle;

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
#endif
