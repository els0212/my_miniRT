/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 00:28:14 by hyi               #+#    #+#             */
/*   Updated: 2021/01/03 15:28:29 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_memset(char **line, size_t size)
{
	size_t	st;

	if (!(*line = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	st = 0;
	while (st < size)
		*(*line + st++) = '\0';
	return (0);
}

int		ft_get_new_line_idx(char *buf)
{
	int	st;

	st = 0;
	while (buf[st])
	{
		if (buf[st] == '\n')
			return (st);
		st++;
	}
	return (-1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	st;

	st = 0;
	while (src[st] && st + 1 < dstsize)
	{
		dst[st] = src[st];
		st++;
	}
	if (dstsize > 0)
		dst[st] = '\0';
	return (0);
}

void	ft_resize_and_copy(char **line, char *buf, int st, int ed)
{
	char	*temp;
	int		mem_size;
	int		line_len;

	line_len = ft_get_len(*line);
	mem_size = line_len + ed - st + 1;
	ft_memset(&temp, mem_size);
	if (*line)
	{
		ft_strlcpy(temp, *line, line_len + 1);
		free(*line);
		*line = 0;
	}
	ft_strlcpy(temp + line_len, buf, ed - st + 1);
	*line = temp;
}

char	*ft_strdup(char *str)
{
	char	*ret;
	int		st;

	if (!(ret = (char *)malloc(sizeof(char) * (ft_get_len(str) + 1))))
		return (0);
	st = 0;
	while (str[st])
	{
		ret[st] = str[st];
		st++;
	}
	ret[st] = '\0';
	return (ret);
}
