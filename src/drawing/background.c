/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:45:21 by maliew            #+#    #+#             */
/*   Updated: 2023/02/02 22:51:34 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_background_color(t_ctx *ctx)
{
	t_mlxx_img	*buffer;
	
	buffer = mlxx_new_rect(ctx, SCREEN_WIDTH, SCREEN_HEIGHT / 2, ctx->ceiling);
	mlxx_copy_image(ctx->img, buffer, 0, 0);
	buffer = mlxx_new_rect(ctx, SCREEN_WIDTH, SCREEN_HEIGHT / 2, ctx->floor);
	mlxx_copy_image(ctx->img, buffer, 0, SCREEN_HEIGHT / 2);
}