/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_rt_2.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:33:47 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:33:49 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_RT_2_H
# define FT_PARSE_RT_2_H
# include "ft_struct.h"
# include "ft_parse_utils_1.h"

int					ft_ins_plane(char **chunks, t_compo *compo, int size);
int					ft_ins_square(char **chunks, t_compo *compo, int size);
int					ft_ins_cylinder(char **chunks, t_compo *compo, int size);
int					ft_ins_triangle(char **chunks, t_compo *compo, int size);
#endif
