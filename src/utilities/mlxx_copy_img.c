/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxx_copy_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:21:10 by maliew            #+#    #+#             */
/*   Updated: 2022/12/18 12:36:40 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mlxx_ispixelblack(char *buffer, int pixel)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if ((buffer[pixel + i] | 0x00) != 0x00)
			return (0);
	}
	return (1);
}

static int	mlxx_get_start_value(int num)
{
	if (num < 0)
		return (-num);
	else
		return (-1);
}

void	mlxx_copy_pixel(t_mlxx_data_addr d, t_mlxx_data_addr s)
{
	d.address[d.pixel + 0] = s.address[s.pixel + 0];
	d.address[d.pixel + 1] = s.address[s.pixel + 1];
	d.address[d.pixel + 2] = s.address[s.pixel + 2];
	d.address[d.pixel + 3] = s.address[s.pixel + 3];
}

/*
** https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html
** https://gontjarow.github.io/MiniLibX/mlx-tutorial-create-image.html
*/
void	mlxx_copy_image(t_mlxx_img *des, t_mlxx_img *src, int x, int y)
{
	t_mlxx_data_addr	d;
	t_mlxx_data_addr	s;
	int					i;
	int					j;

	if (des == NULL || src == NULL)
		return ;
	s.address = mlx_get_data_addr(src->img, &s.pixel_bits, &s.size_line,
			&s.endian);
	d.address = mlx_get_data_addr(des->img, &d.pixel_bits, &d.size_line,
			&d.endian);
	j = mlxx_get_start_value(y);
	while (++j < src->height && y + j < des->height)
	{
		i = mlxx_get_start_value(x);
		while (++i < src->width && x + i < des->width)
		{
			s.pixel = ((j) * s.size_line) + ((i) * 4);
			d.pixel = ((y + j) * d.size_line) + ((x + i) * 4);
			if (!mlxx_ispixelblack(s.address, s.pixel))
				mlxx_copy_pixel(d, s);
		}
	}
}
