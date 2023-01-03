/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_ctx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:26:10 by maliew            #+#    #+#             */
/*   Updated: 2023/01/03 16:38:41 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_init_ctx(t_ctx *ctx)
{
	ctx->map_width = 0;
	ctx->map_height = 0;
	ctx->north = NULL;
	ctx->south = NULL;
	ctx->east = NULL;
	ctx->west = NULL;
	ctx->floor = 0;
	ctx->ceiling = 0;
	ctx->floor_parsed = 0;
	ctx->ceiling_parsed = 0;
	
	ctx->mlx_data = ft_calloc(1, sizeof(t_mlxx_data_addr));
	ctx->player = ft_calloc(1, sizeof(t_player)); //TODO: Remember to free this
	if (!ctx->player)
		ft_printf("Error initializing player, out of memory");
	ctx->player->delta_x = cos(ctx->player->angle) * 5;
	ctx->player->delta_y = sin(ctx->player->angle) * 5;
	ctx->player->x = 300;
	ctx->player->y = 300;
}
