/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:44:58 by echai             #+#    #+#             */
/*   Updated: 2023/01/30 18:39:48 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Puts a pixel on the screen
 * 
 * @param ctx 
 * @param x x-coordinate
 * @param y y-coordinate
 * @param color 
 */
void	put_pixel(t_ctx *ctx, int x, int y, int color)
{
	char	*dst;

	dst = ctx->mlx_data->address
		+ (y * ctx->mlx_data->size_line + x * (ctx->mlx_data->pixel_bits / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Draws a line from point A to point B
 * 
 * @param ctx 
 * @param line struct containing x1, y1, x2, y2
 * @param color Color to draw the line in
 */
void	draw_line(t_ctx *ctx, t_line line, int color)
{
	float	delta_x;
	float	delta_y;
	int		dist;

	delta_x = line.x2 - line.x1;
	delta_y = line.y2 - line.y1;
	dist = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= dist;
	delta_y /= dist;
	while (dist)
	{
		put_pixel(ctx, line.x1, line.y1, color);
		line.x1 += delta_x;
		line.y1 += delta_y;
		--dist;
	}
}

/**
 * @brief Draws a 64x64 square in a specific color
 * 
 * @param ctx 
 * @param square struct containing x, y, size
 * @param color Color to draw in
 */
void	draw_square(t_ctx *ctx, t_square square, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < square.size)
	{
		j = -1;
		while (++j < square.size)
		{
			if (i == 0 || j == 0 || i == square.size || j == square.size)
				put_pixel(ctx, square.x + j, square.y + i, 0x00000000);
			else
				put_pixel(ctx, square.x + j, square.y + i, color);
		}
	}
}

/**
 * @brief Draws the player on the screen
 * 
 * Change `size` if you wish to change the size of the player rendered
 * 
 * @param ctx Reference to t_ctx object
 * @param color color hexcode in 0xAARRGGBB format
 * @param size size of the player to draw
 */
void	draw_player(t_ctx *ctx, int color, int size)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	i = -1;
	start_x = ctx->player->x - size / 2;
	start_y = ctx->player->y - size / 2;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			put_pixel(ctx, start_x + j, start_y + i, color);
	}
}
