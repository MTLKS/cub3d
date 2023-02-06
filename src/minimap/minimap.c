/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:21:40 by maliew            #+#    #+#             */
/*   Updated: 2023/02/06 20:46:54 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map_image(t_ctx *ctx, t_mlxx_img **squares, int size)
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
				mlxx_copy_image(ctx->map_image, squares[1], x * size, y * size);
			else if (ctx->map[y][x] == '2')
				mlxx_copy_image(ctx->map_image, squares[2], x * size, y * size);
			else
				mlxx_copy_image(ctx->map_image, squares[0], x * size, y * size);
		}
	}
}

int	generate_map_image(t_ctx *ctx)
{
	int			size;
	t_mlxx_img	**squares;

	size = 16;
	squares = malloc(3 * sizeof(t_mlxx_img *));
	squares[0] = mlxx_new_rect(ctx, size, size, 0x00111111);
	squares[1] = mlxx_new_rect(ctx, size, size, 0x00FFFFFF);
	squares[2] = mlxx_new_rect(ctx, size, size, 0x0077FF77);
	ctx->map_image = mlxx_new_img(ctx->mlx, ctx->map_width * size,
			ctx->map_height * size);
	if (ctx->map_image == NULL)
		return (1);
	draw_map_image(ctx, squares, size);
	return (0);
}

int	generate_minimap_image(t_ctx *ctx)
{
	int			size;
	t_mlxx_img	*arrow;
	t_mlxx_img	*overlay;

	size = SCREEN_HEIGHT / 4;
	ctx->minimap_image = mlxx_new_rect(ctx, size, size, 0x00111111);
	if (ctx->minimap_image == NULL)
		return (1);
	mlxx_copy_image(ctx->minimap_image, ctx->map_image,
		SCREEN_HEIGHT / 8 - ctx->player->x / 64 * 16,
		SCREEN_HEIGHT / 8 - ctx->player->y / 64 * 16);
	mlxx_rotate_img(ctx->mlx, &ctx->minimap_image,
		90 + ctx->player->angle * 180 / PI);
	arrow = mlxx_xpm_file_to_img(ctx->mlx, "assets/arrow.xpm");
	mlxx_copy_image(ctx->minimap_image, arrow, SCREEN_HEIGHT / 8 - 1,
		SCREEN_HEIGHT / 8 - 1);
	mlxx_destroy_img(ctx->mlx, arrow);
	overlay = mlxx_xpm_file_to_img(ctx->mlx, "assets/overlay.xpm");
	mlxx_copy_image(ctx->minimap_image, overlay, 0, 0);
	mlxx_destroy_img(ctx->mlx, overlay);
	mlxx_copy_image(ctx->img, ctx->minimap_image, 0, 0);
	mlxx_destroy_img(ctx->mlx, ctx->minimap_image);
	return (0);
}
