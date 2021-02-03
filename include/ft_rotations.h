/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:35:00 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:35:01 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ROTATIONS_H
# define FT_ROTATIONS_H
# include "ft_struct.h"

t_vector	ft_rotate_x(t_vector now, double angle);
t_vector	ft_rotate_y(t_vector now, double angle);
t_vector	ft_rotate_z(t_vector now, double angle);
#endif
