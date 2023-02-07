/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxx_rotate_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 00:41:57 by maliew            #+#    #+#             */
/*   Updated: 2023/02/07 18:05:27 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlxx_rotate_pixel(t_mlxx_img *des, t_mlxx_img *src, int p[4])
{
	t_mlxx_data_addr	d;
	t_mlxx_data_addr	s;

	s.address = mlx_get_data_addr(src->img, &s.pixel_bits, &s.size_line,
			&s.endian);
	d.address = mlx_get_data_addr(des->img, &d.pixel_bits, &d.size_line,
			&d.endian);
	s.pixel = p[3] * s.size_line + p[2] * 4;
	d.pixel = p[1] * d.size_line + p[0] * 4;
	mlxx_copy_pixel(d, s);
}

/**
 * @brief Rotates image by a certain degree.
 * 
 * @param mlx Mlx pointer
 * @param img Pointer to mlxx img
 * @param degree Degree to rotate image
*/
void	mlxx_rotate_img(void *mlx, t_mlxx_img **img, int degree)
{
	t_mlxx_img	*new_img;
	int			p[4];

	new_img = mlxx_new_img(mlx, (*img)->width, (*img)->height);
	p[1] = -1;
	while (++p[1] < (*img)->height)
	{
		p[0] = -1;
		while (++p[0] < (*img)->width)
		{
			p[2] = round((p[0] - (*img)->width / 2) * cos(degree * M_PI / 180)
					- (p[1] - (*img)->height / 2) * sin(degree * M_PI / 180)
					+ (*img)->width / 2);
			p[3] = round((p[0] - (*img)->width / 2) * sin(degree * M_PI / 180)
					+ (p[1] - (*img)->height / 2) * cos(degree * M_PI / 180)
					+ (*img)->height / 2);
			if (!(p[2] < 0 || p[2] >= (*img)->width
					|| p[3] < 0 || p[3] >= (*img)->height))
				mlxx_rotate_pixel(new_img, *img, p);
		}
	}
	mlxx_destroy_img(mlx, *img);
	*img = new_img;
}
