/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxx_new_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 00:50:20 by maliew            #+#    #+#             */
/*   Updated: 2022/12/18 12:36:38 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlxx_img	*mlxx_new_img(void *mlx, int width, int height)
{
	t_mlxx_img	*res;

	res = (t_mlxx_img *)malloc(sizeof(t_mlxx_img));
	res->img = mlx_new_image(mlx, width, height);
	res->width = width;
	res->height = height;
	return (res);
}
