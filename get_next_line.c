/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 00:28:24 by hyi               #+#    #+#             */
/*   Updated: 2021/01/07 20:56:51 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_miniRT.h"

int	ft_while_loop(char **line, char *buf, char **buf_ref)
{
	int		idx;
	int		st;

	idx = ft_get_new_line_idx(buf);
	if (idx < 0)
		ft_resize_and_copy(line, buf, 0, BUFFER_SIZE);
	else
	{
		ft_resize_and_copy(line, buf, 0, idx);
		*buf_ref = (idx + 1 < (int)ft_strlen(buf) && *(buf + idx + 1))
			? ft_strdup(&buf[idx + 1]) : 0;
		return (1);
	}
	st = 0;
	while (st < BUFFER_SIZE)
		buf[st++] = '\0';
	return (0);
}

int	ft_proc_buf_ref(char **line, char **buf_ref)
{
	int		idx;
	char	*del;
	int		ret;

	idx = ft_get_new_line_idx(*buf_ref);
	del = *buf_ref;
	if (idx >= 0)
	{
		ft_resize_and_copy(line, *buf_ref, 0, idx);
		*buf_ref = (idx + 1 < (int)ft_strlen(*buf_ref) && *(*buf_ref + idx + 1))
			? ft_strdup(*buf_ref + idx + 1) : 0;
		ret = 1;
	}
	else
	{
		ft_resize_and_copy(line, *buf_ref, 0, ft_strlen(*buf_ref));
		*buf_ref = 0;
		ret = 0;
	}
	free(del);
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*buf_ref;
	char		*buf;
	ssize_t		rd;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = 0;
	if (buf_ref)
		if (ft_proc_buf_ref(line, &buf_ref))
			return (1);
	ft_memset(&buf, BUFFER_SIZE + 1);
	while ((rd = read(fd, buf, BUFFER_SIZE)) > 0)
		if (ft_while_loop(line, buf, &buf_ref))
			break ;
	free(buf);
	if (!*line)
		ft_memset(line, 1);
	if (rd > 0)
		return (1);
	return (rd < 0 ? -1 : 0);
}
