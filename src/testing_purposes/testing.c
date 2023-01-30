/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:59:24 by echai             #+#    #+#             */
/*   Updated: 2023/01/30 18:39:10 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Create a square fill with a certain color.
*/
t_mlxx_img	*square(t_ctx *ctx, int color)
{
	t_mlxx_img			*img;
	t_mlxx_data_addr	addr;
	int					i;
	int					j;

	img = mlxx_new_img(ctx->mlx, 64, 64);
	addr.address = mlx_get_data_addr(img->img, &addr.pixel_bits, &addr.size_line, &addr.endian);
	j = -1;
	while (++j < 64)
	{
		i = -1;
		while (++i < 64)
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
