/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:26:46 by maliew            #+#    #+#             */
/*   Updated: 2023/02/06 15:50:39 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle_door(t_ctx *ctx, int x, int y)
{
	if (ft_strchr("23",
		ctx->map[((int)ctx->player->y) / 64][((int)ctx->player->x) / 64]) != 0)
			return ;
	if (ft_strchr("2", ctx->map[y][x]) != 0)
		ctx->map[y][x] = '3';
	else if (ft_strchr("3", ctx->map[y][x]) != 0)
		ctx->map[y][x] = '2';
}

/**
 * @brief Checks if 'w' or 's' keys are pressed and move player
 * accordingly.
 * 
 * @param ctx Context struct
*/
void	move_player_straight(t_ctx *ctx)
{
	float	pos_x;
	float	pos_y;

	if (ctx->key.w)
	{
		pos_x = ctx->player->x + ctx->player->delta_x * ctx->key.shift;
		pos_y = ctx->player->y + ctx->player->delta_y * ctx->key.shift;
	}
	if (ctx->key.s)
	{
		pos_x = ctx->player->x - ctx->player->delta_x * ctx->key.shift;
		pos_y = ctx->player->y - ctx->player->delta_y * ctx->key.shift;
	}
	if ((ctx->key.w || ctx->key.s) && !(ctx->key.w && ctx->key.s))
	{
		if (ft_strchr("03NSEW",
				ctx->map[(int)((pos_y) / 64)][(int)((pos_x) / 64)]) != 0)
		{
			ctx->player->x = pos_x;
			ctx->player->y = pos_y;
		}
	}
}

/**
 * @brief Checks if 'a' or 'd' keys are pressed and move player
 * accordingly.
 * 
 * @param ctx Context struct
*/
void	move_player_strafe(t_ctx *ctx)
{
	float	temp_angle;

	if (ctx->key.a)
	{
		temp_angle = ctx->player->angle - PI / 2;
		if (temp_angle < 0)
			temp_angle += 2 * PI;
	}
	if (ctx->key.d)
	{
		temp_angle = ctx->player->angle + PI / 2;
		if (temp_angle > 2 * PI)
			temp_angle -= 2 * PI;
	}
	if ((ctx->key.a || ctx->key.d) && !(ctx->key.a && ctx->key.d))
	{
		if (ft_strchr("0NSEW",
				ctx->map[(int)((ctx->player->y + sin(temp_angle) * 2) / 64)]
			[(int)((ctx->player->x + cos(temp_angle) * 2) / 64)]) != 0)
		{
			ctx->player->x += cos(temp_angle) * 2;
			ctx->player->y += sin(temp_angle) * 2;
		}
	}
}

/**
 * @brief Checks for key presses and moves player accordingly.
 * 
 * @param ctx Context struct
*/
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
