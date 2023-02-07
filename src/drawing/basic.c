/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:44:58 by echai             #+#    #+#             */
/*   Updated: 2023/02/07 18:47:17 by maliew           ###   ########.fr       */
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
