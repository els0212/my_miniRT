/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:33:54 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:33:58 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_UTILS_H
# define FT_LIST_UTILS_H
# include "ft_struct.h"

void		ft_add_last(t_object **list, t_object *obj);
void		ft_add_light_last(t_lht **list, t_lht *obj);
void		ft_add_camera_last(t_cam **list, t_cam *obj);
int			ft_get_cam_size(t_cam *list);
t_cam		*ft_get_cam(t_cam *list, int i);
#endif
