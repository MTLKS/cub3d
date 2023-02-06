/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:32:07 by maliew            #+#    #+#             */
/*   Updated: 2023/02/06 00:57:00 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Set player position according to map, returns 1 if player position
 * is already set.
 * 
 * @param ctx Context struct
 * @param row Row position
 * @param col Column position
 * @param dir Direction 'N', 'S', 'E', 'W'
 * 
 * @return 0 if set, 1 if position is already set
*/
static int	cub_set_player_position(t_ctx *ctx, int row, int col, char dir)
{
	if (ctx->player->x != 0 && ctx->player->y != 0)
		return (1);
	ctx->player->x = col * 64 + 32;
	ctx->player->y = row * 64 + 32;
	if (dir == 'E')
		ctx->player->angle = 0;
	else if (dir == 'S')
		ctx->player->angle = 90;
	else if (dir == 'W')
		ctx->player->angle = 180;
	else if (dir == 'N')
		ctx->player->angle = 270;
	ctx->player->angle = ctx->player->angle * PI / 180;
	return (0);
}

/**
 * @brief If the tile is a floor tile, checks 8 surrounding tiles
 * to make sure there is no empty space.
 * 
 * @param ctx Context struct
 * @param row Row position
 * @param col Column position
 * 
 * @return 0 if valid, 1 if not valid
*/
static int	cub_check_surrounding_tiles(t_ctx *ctx, int row, int col)
{
	int	i;
	int	j;

	if (ctx->map[row][col] != '0')
		return (0);
	i = -2;
	while (++i < 2)
	{
		j = -2;
		while (++j < 2)
		{
			if (row + i >= 0 && row + i <= ctx->map_height && col + j >= 0
				&& col + j <= ctx->map_width
				&& (ctx->map[row + i][col + j] == 0
				|| ft_strchr("012NSEWD", ctx->map[row + i][col + j]) == 0))
				return (1);
		}
	}
	return (0);
}

/**
 * @brief Go through the map array and check if it is a valid character and
 * there are no empty spaces next to floor tiles in the map.
 * 
 * @param ctx Context struct
 * 
 * @return 0 if valid, 1 if not valid
*/
static int	cub_check_map_array(t_ctx *ctx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < ctx->map_height)
	{
		j = -1;
		while (++j < ctx->map_width)
		{
			if (ft_strchr(" 012NSEWD", ctx->map[i][j]) == 0)
				return (1);
			if (cub_check_surrounding_tiles(ctx, i, j))
				return (1);
			if (ft_strchr("NSEW", ctx->map[i][j]) != 0 && ctx->map[i][j] &&
				cub_set_player_position(ctx, i, j, ctx->map[i][j]))
				return (1);
		}
	}
	return (0);
}

/**
 * @brief Check if the struct is parsed and there are no missing information.
 * Then checks the map if it is valid.
 * 
 * @param ctx Context struct
 * 
 * @return 0 if valid, 1 if not valid
*/
int	cub_check_struct(t_ctx *ctx)
{
	if (ctx->map_width == 0 || ctx->map_height == 0 || ctx->north == NULL
		|| ctx->south == NULL || ctx->east == NULL || ctx->west == NULL
		|| ctx->ceiling_parsed == 0 || ctx->floor_parsed == 0)
		return (1);
	if (cub_check_map_array(ctx))
		return (1);
	return (0);
}
