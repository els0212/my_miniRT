/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:30:36 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:30:46 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FREE_UTILS_H
# define FT_FREE_UTILS_H
# include "ft_struct.h"

void	ft_free_amb(t_amb *amb);
void	ft_free_cam(t_cam *cam);
void	ft_free_lht(t_lht *lht);
void	ft_free_obj(t_object *obj);
void	ft_free_compo(t_compo *compo);
#endif
