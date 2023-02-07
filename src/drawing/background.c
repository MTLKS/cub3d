/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:45:21 by maliew            #+#    #+#             */
/*   Updated: 2023/02/07 18:54:34 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Create background image from two colors specified in the map file.
 * 
 * @param ctx Context struct
*/
void	create_background_image(t_ctx *ctx)
{
	t_mlxx_img	*buffer;

	ctx->background_image = mlxx_new_img(ctx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	buffer = mlxx_new_rect(ctx, SCREEN_WIDTH, SCREEN_HEIGHT / 2, ctx->ceiling);
	mlxx_copy_image(ctx->background_image, buffer, 0, 0);
	mlxx_destroy_img(ctx->mlx, buffer);
	buffer = mlxx_new_rect(ctx, SCREEN_WIDTH, SCREEN_HEIGHT / 2, ctx->floor);
	mlxx_copy_image(ctx->background_image, buffer, 0, SCREEN_HEIGHT / 2);
	mlxx_destroy_img(ctx->mlx, buffer);
}
