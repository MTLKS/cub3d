/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:21:40 by maliew            #+#    #+#             */
/*   Updated: 2023/02/02 22:50:27 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map_image(t_ctx *ctx, t_mlxx_img *black, t_mlxx_img *white,
	int size)
{
	int	y;
	int	x;

	y = -1;
	while (++y < ctx->map_height)
	{
		x = -1;
		while (++x < ctx->map_width)
		{
			if (ctx->map[y][x] == '1')
				mlxx_copy_image(ctx->map_image, white, x * size, y * size);
			else
				mlxx_copy_image(ctx->map_image, black, x * size, y * size);
		}
	}
}

int	generate_map_image(t_ctx *ctx)
{
	int			size;
	t_mlxx_img	*black;
	t_mlxx_img	*white;

	size = 16;
	black = mlxx_new_rect(ctx, size, size, 0x00111111);
	white = mlxx_new_rect(ctx, size, size, 0x00FFFFFF);
	ctx->map_image = mlxx_new_img(ctx->mlx, ctx->map_width * size,
			ctx->map_height * size);
	if (ctx->map_image == NULL)
		return (1);
	draw_map_image(ctx, black, white, size);
	return (0);
}

int	generate_minimap_image(t_ctx *ctx)
{
	int			size;
	t_mlxx_img	*square;

	size = SCREEN_HEIGHT / 4;
	ctx->minimap_image = mlxx_new_img(ctx->mlx, size, size);
	if (ctx->minimap_image == NULL)
		return (1);
	mlxx_copy_image(ctx->minimap_image, ctx->map_image,
		SCREEN_HEIGHT / 8 - ctx->player->x / 64 * 16,
		SCREEN_HEIGHT / 8 - ctx->player->y / 64 * 16);
	square = mlxx_new_rect(ctx, 3, 3, 0x00FF0000);
	mlxx_copy_image(ctx->minimap_image, square, SCREEN_HEIGHT / 8 - 1,
		SCREEN_HEIGHT / 8 - 1);
	mlxx_destroy_img(ctx->mlx, square);
	mlxx_copy_image(ctx->img, ctx->minimap_image, 0, 0);
	mlxx_destroy_img(ctx->mlx, ctx->minimap_image);
	return (0);
}
