/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:34:17 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:52:41 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RENDER_H
# define FT_RENDER_H
# include "ft_shader.h"
# include "ft_save.h"
# include "../mlx/mlx.h"
# include "ft_list_utils.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	ft_render_loop(t_scene *scene, t_cam *cam, int i);
int		ft_render(t_scene *scene);
#endif
