/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:30:56 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:30:58 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_UTILS_H
# define FT_MATH_UTILS_H
# include "ft_struct.h"

t_vector			ft_cross_product(t_vector a, t_vector b);
double				ft_dot_product(t_vector a, t_vector b);
double				ft_get_dist(t_vector a, t_vector b);
#endif
