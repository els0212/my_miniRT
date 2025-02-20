/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:36:13 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:36:13 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_UTILS_H
# define GET_NEXT_LINE_UTILS_H
# include "ft_libft.h"

int					ft_memset(char **line, size_t size);
int					ft_get_new_line_idx(char *buf);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				ft_resize_and_copy(char **line, char *buf, int st, int ed);
char				*ft_strdup(char *str);
#endif
