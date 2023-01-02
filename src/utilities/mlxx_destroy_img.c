/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxx_destroy_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 00:52:50 by maliew            #+#    #+#             */
/*   Updated: 2022/12/18 12:36:39 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlxx_destroy_img(void *mlx, t_mlxx_img *img)
{
	mlx_destroy_image(mlx, img->img);
	free(img);
}
