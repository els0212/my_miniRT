/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:37:12 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:37:13 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHADER_H
# define FT_SHADER_H
# include "ft_ray_hit_2.h"

t_color	ft_specular(t_lht *now, t_ray ray);
t_color	ft_get_light_color(t_lht *now, t_object *objs, t_ray ray);
t_color	ft_shader(t_lht *lht, t_object *objs, t_ray ray);
int		ft_mix_color(t_compo *compo, t_ray *ray);
#endif
