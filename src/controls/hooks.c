/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:42:35 by echai             #+#    #+#             */
/*   Updated: 2023/02/06 16:23:06 by echai            ###   ########.fr       */
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
	ctx->img = mlxx_new_img(ctx->mlx, 1024, 512);
	ctx->mlx_data->address = mlx_get_data_addr(ctx->img->img,
			&ctx->mlx_data->pixel_bits,
			&ctx->mlx_data->size_line, &ctx->mlx_data->endian);
	move_player(ctx);
	mlxx_copy_image(ctx->img, ctx->background_image, 0, 0);
	cast_rays(ctx);
	generate_minimap_image(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img->img, 0, 0);
	mlxx_destroy_img(ctx->mlx, ctx->img);
	return (0);
}
