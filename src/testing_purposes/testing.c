/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:59:24 by echai             #+#    #+#             */
/*   Updated: 2023/02/02 22:43:38 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
