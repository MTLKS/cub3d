/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxx_rotate_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 00:41:57 by maliew            #+#    #+#             */
/*   Updated: 2023/02/06 21:29:35 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlxx_rotate_pixel(t_mlxx_img *des, t_mlxx_img *src, int i, int j, int new_i, int new_j)
{
	t_mlxx_data_addr	d;
	t_mlxx_data_addr	s;

	s.address = mlx_get_data_addr(src->img, &s.pixel_bits, &s.size_line,
			&s.endian);
	d.address = mlx_get_data_addr(des->img, &d.pixel_bits, &d.size_line,
			&d.endian);
	s.pixel = j * s.size_line + i * 4;
	d.pixel = new_j * d.size_line + new_i * 4;
	mlxx_copy_pixel(d, s);
}

void	mlxx_rotate_img(void *mlx, t_mlxx_img **img, int degree)
{
	t_mlxx_img	*new_img;
	int			i;
	int			j;
	int			new_i;
	int			new_j;

	new_img = mlxx_new_img(mlx, (*img)->width, (*img)->height);
	j = -1;
	while (++j < (*img)->height)
	{
		i = -1;
		while (++i < (*img)->width)
		{
			new_i = round((i - (*img)->width / 2) * cos(degree * M_PI / 180)
					- (j - (*img)->height / 2) * sin(degree * M_PI / 180)
					+ (*img)->width / 2);
			new_j = round((i - (*img)->width / 2) * sin(degree * M_PI / 180)
					+ (j - (*img)->height / 2) * cos(degree * M_PI / 180)
					+ (*img)->height / 2);
			if (!(new_i < 0 || new_i >= (*img)->width
					|| new_j < 0 || new_j >= (*img)->height))
				mlxx_rotate_pixel(new_img, *img, new_i, new_j, i, j);
		}
	}
	mlxx_destroy_img(mlx, *img);
	*img = new_img;
}
