/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:32:07 by maliew            #+#    #+#             */
/*   Updated: 2023/01/02 17:29:50 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				|| ft_strchr("01NSEWD", ctx->map[row + i][col + j]) == 0))
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
			if (ft_strchr(" 01NSEWD", ctx->map[i][j]) == 0)
				return (1);
			if (cub_check_surrounding_tiles(ctx, i, j))
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
