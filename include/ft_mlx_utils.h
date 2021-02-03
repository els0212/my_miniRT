/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:31:24 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:33:05 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_UTILS_H
# define FT_MLX_UTILS_H
# define CAM_UP 126
# define CAM_DOWN 125
# define ESCAPE 53
# define KEYPRESS 2
# define KEYPRESSMASK 0
# define DESTROYNOTIFY 17
# define STRUCTURENOTIFYMASK 131072
# include "ft_render.h"

int		ft_close(void);
void	ft_mlx_init(t_scene *scene, t_res *res, t_img *img, t_mlx *mlx);
int		ft_rerender(int key, t_scene *scene);
#endif
