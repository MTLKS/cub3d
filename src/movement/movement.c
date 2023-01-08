/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:26:46 by maliew            #+#    #+#             */
/*   Updated: 2023/01/08 21:36:32 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_straight(t_ctx *ctx)
{
	if (ctx->key.w)
	{
		if (strchr("0NSEW",
				ctx->map[(int)((ctx->player->y + ctx->player->delta_y) / 64)]
			[(int)((ctx->player->x + ctx->player->delta_x) / 64)]) != 0)
		{
			ctx->player->x += ctx->player->delta_x;
			ctx->player->y += ctx->player->delta_y;
		}
	}
	if (ctx->key.s)
	{
		if (strchr("0NSEW",
				ctx->map[(int)((ctx->player->y - ctx->player->delta_y) / 64)]
			[(int)((ctx->player->x - ctx->player->delta_x) / 64)]) != 0)
		{
			ctx->player->x -= ctx->player->delta_x;
			ctx->player->y -= ctx->player->delta_y;
		}
	}
}

void	move_player_strafe(t_ctx *ctx)
{
	float	temp_angle;

	if (ctx->key.a)
	{
		temp_angle = ctx->player->angle - PI / 2;
		if (temp_angle < 0)
			temp_angle += 2 * PI;
		if (strchr("0NSEW",
				ctx->map[(int)((ctx->player->y + sin(temp_angle) * 2) / 64)]
			[(int)((ctx->player->x + cos(temp_angle) * 2) / 64)]) != 0)
		{
			ctx->player->x += cos(temp_angle) * 2;
			ctx->player->y += sin(temp_angle) * 2;
		}
	}
	if (ctx->key.d)
	{
		temp_angle = ctx->player->angle + PI / 2;
		if (temp_angle > 2 * PI)
			temp_angle -= 2 * PI;
		if (strchr("0NSEW",
				ctx->map[(int)((ctx->player->y + sin(temp_angle) * 2) / 64)]
			[(int)((ctx->player->x + cos(temp_angle) * 2) / 64)]) != 0)
		{
			ctx->player->x += cos(temp_angle) * 2;
			ctx->player->y += sin(temp_angle) * 2;
		}
	}
}

void	move_player(t_ctx *ctx)
{
	move_player_straight(ctx);
	move_player_strafe(ctx);
	if (ctx->key.left)
	{
		ctx->player->angle -= 0.05;
		if (ctx->player->angle < 0)
			ctx->player->angle += 2 * PI;
	}
	if (ctx->key.right)
	{
		ctx->player->angle += 0.05;
		if (ctx->player->angle > 2 * PI)
			ctx->player->angle -= 2 * PI;
	}
	ctx->player->delta_x = cos(ctx->player->angle) * 2;
	ctx->player->delta_y = sin(ctx->player->angle) * 2;
}
