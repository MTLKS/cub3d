/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:42:35 by echai             #+#    #+#             */
/*   Updated: 2023/01/03 16:39:07 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Renders the screen at each mlx loop
 * 
 * @param ctx 
 * @return int 
 */
int	render(t_ctx *ctx)
{
	ctx->img = mlx_new_image(ctx->mlx, 1024, 512);
	ctx->mlx_data->address = mlx_get_data_addr(ctx->img,
			&ctx->mlx_data->pixel_bits,
			&ctx->mlx_data->size_line, &ctx->mlx_data->endian);
	draw_map(ctx);
	// draw_rays(ctx);
	// draw_player(ctx, 0x00FFFF00, 8);
	// mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img, 0, 0);
	return (0);
}

/**
 * @brief Detects keypress and performs action
 * 
 * @param keycode key pressed
 * @param ctx 
 * @return int 
 */
int	key_hook(int keycode, t_ctx *ctx)
{
	if (keycode == KEY_W)
	{
		ctx->player->x += ctx->player->delta_x;
		ctx->player->y += ctx->player->delta_y;
	}
	else if (keycode == KEY_A)
	{
		ctx->player->angle -= 0.1;
		if (ctx->player->angle < 0)
			ctx->player->angle += 2 * PI;
		ctx->player->delta_x = cos(ctx->player->angle) * 5;
		ctx->player->delta_y = sin(ctx->player->angle) * 5;
	}
	else if (keycode == KEY_S)
	{
		ctx->player->x -= ctx->player->delta_x;
		ctx->player->y -= ctx->player->delta_y;
	}
	else if (keycode == KEY_D)
	{
		ctx->player->angle += 0.1;
		if (ctx->player->angle > 2 * PI)
			ctx->player->angle -= 2 * PI;
		ctx->player->delta_x = cos(ctx->player->angle) * 5;
		ctx->player->delta_y = sin(ctx->player->angle) * 5;
	}
	else if (keycode == KEY_ESC)
	{
		ft_printf("ESC pressed.\n"); // Change to quit and free later
		system("leaks -q cub3d");
		exit(0);
	}
	return (keycode);
}

// /**
//  * @brief Just an intermediary to close the game
//  * 
//  * @param ctx 
//  * @return int 
//  */
// int	close_window(t_ctx *ctx)
// {
// 	end_game(ctx);
// 	return (1);
// }
