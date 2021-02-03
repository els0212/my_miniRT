/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:35:58 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:35:59 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "get_next_line_utils.h"
# include <fcntl.h>
# include <unistd.h>
# define BUFFER_SIZE 1024

int					ft_while_loop(char **line, char *buf, char **buf_ref);
int					ft_proc_buf_ref(char **line, char **buf_ref);
int					get_next_line(int fd, char **line);
#endif
