/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:35:33 by hyi               #+#    #+#             */
/*   Updated: 2021/02/03 16:35:36 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

int					ft_get_chunks_size(char **chunks);
int					ft_get_sign(const char *nptr, int *sign);
int					ft_atoi(const char *nptr);
double				ft_atod(const char *nptr);
void				ft_swap(double *a, double *b);
#endif
