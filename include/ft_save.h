/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:35:11 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:35:13 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SAVE_H
# define FT_SAVE_H
# define HEADERSIZE 54
# include "get_next_line.h"

int		**ft_init_buffer(int width, int height);
void	ft_free_buffer(int **del, int height);
int		ft_save_bmp(char *filename, int **target, int width, int height);
#endif
