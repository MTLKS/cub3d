/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:59:24 by echai             #+#    #+#             */
/*   Updated: 2023/02/01 11:21:39 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Create a rectangle fill with a certain color.
*/
t_mlxx_img	*mlxx_new_rect(t_ctx *ctx, int width, int height, int color)
{
	t_mlxx_img			*img;
	t_mlxx_data_addr	addr;
	int					i;
	int					j;

	img = mlxx_new_img(ctx->mlx, width, height);
	addr.address = mlx_get_data_addr(img->img, &addr.pixel_bits,
			&addr.size_line, &addr.endian);
	j = -1;
	while (++j < height)
	{
		i = -1;
		while (++i < width)
		{
			addr.pixel = (j * addr.size_line) + (i * 4);
			addr.address[addr.pixel + 0] = cub_get_b(color);
			addr.address[addr.pixel + 1] = cub_get_g(color);
			addr.address[addr.pixel + 2] = cub_get_r(color);
			addr.address[addr.pixel + 3] = cub_get_t(color);
		}
	}
	return (img);
}


/**
 * @brief Draws a temporary map
 * 
 * @param ctx 
 */
void	draw_map(t_ctx *ctx)
{
	int			x;
	int			y;
	int			square_size;
	t_square	square;

	y = -1;
	square_size = 64;
	while (++y < ctx->map_height)
	{
		x = -1;
		while (++x < ctx->map_width)
		{
			square.x = x * square_size;
			square.y = y * square_size;
			square.size = square_size;
			if (ctx->map[y][x] == '1')
				draw_square(ctx, square, 0x00FFFFFF);
			else
				draw_square(ctx, square, 0x00000000);
		}
	}
}
