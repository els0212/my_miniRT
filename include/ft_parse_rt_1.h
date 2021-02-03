/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_rt_1.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:33:43 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:33:44 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_RT_1_H
# define FT_PARSE_RT_1_H
# include "ft_struct.h"
# include "ft_parse_utils_1.h"

int					ft_ins_resolution(char **chunks, t_compo *compo, int size);
int					ft_ins_ambient(char **chunks, t_compo *compo, int size);
int					ft_ins_camera(char **chunks, t_compo *compo, int size);
int					ft_ins_light(char **chunks, t_compo *compo, int size);
int					ft_ins_sphere(char **chunks, t_compo *compo, int size);
#endif
