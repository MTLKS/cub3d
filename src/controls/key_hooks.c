/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:40:48 by maliew            #+#    #+#             */
/*   Updated: 2023/02/07 18:23:19 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Toggles between mouse show and mouse hide.
 * 
 * @param ctx Context struct
*/
static void	toggle_mouse(t_ctx *ctx)
{
	if (ctx->key.mouse)
	{
		mlx_mouse_show();
		ctx->key.mouse = 0;
	}
	else
	{
		mlx_mouse_hide();
		mlx_mouse_move(ctx->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		ctx->key.mouse = 1;
	}
}

int	keydown_hook(int keycode, t_ctx *ctx)
{
	if (keycode == KEY_W)
		ctx->key.w = 1;
	else if (keycode == KEY_A)
		ctx->key.a = 1;
	else if (keycode == KEY_S)
		ctx->key.s = 1;
	else if (keycode == KEY_D)
		ctx->key.d = 1;
	else if (keycode == KEY_LEFT)
		ctx->key.left = 1;
	else if (keycode == KEY_RIGHT)
		ctx->key.right = 1;
	else if (keycode == KEY_SHIFT)
		ctx->key.shift = 2;
	if (keycode == KEY_ESC)
		cub_free_and_exit(ctx);
	return (keycode);
}

int	keyup_hook(int keycode, t_ctx *ctx)
{
	if (keycode == KEY_W)
		ctx->key.w = 0;
	else if (keycode == KEY_A)
		ctx->key.a = 0;
	else if (keycode == KEY_S)
		ctx->key.s = 0;
	else if (keycode == KEY_D)
		ctx->key.d = 0;
	else if (keycode == KEY_LEFT)
		ctx->key.left = 0;
	else if (keycode == KEY_RIGHT)
		ctx->key.right = 0;
	else if (keycode == KEY_E)
	{
		door_handler(ctx);
		ctx->anim_frame = 0;
	}
	else if (keycode == KEY_M)
		toggle_mouse(ctx);
	else if (keycode == KEY_SHIFT)
		ctx->key.shift = 1;
	return (keycode);
}

int	mouse_hook(int x, int y, t_ctx *ctx)
{
	(void) y;
	(void) ctx;
	if (ctx->key.mouse)
	{
		ctx->player->angle += (x - SCREEN_WIDTH / 2) / PI / 128;
		if (ctx->player->angle < 0)
			ctx->player->angle += 2 * PI;
		if (ctx->player->angle > 2 * PI)
			ctx->player->angle -= 2 * PI;
		mlx_mouse_move(ctx->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	return (0);
}
