/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_ctx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:26:10 by maliew            #+#    #+#             */
/*   Updated: 2023/02/09 18:54:22 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_init_key(t_ctx *ctx)
{
	ctx->key.w = 0;
	ctx->key.a = 0;
	ctx->key.s = 0;
	ctx->key.d = 0;
	ctx->key.left = 0;
	ctx->key.right = 0;
	ctx->key.mouse = 0;
	ctx->key.shift = 1;
}

static void	cub_init_imgs(t_ctx *ctx)
{
	ctx->img = NULL;
	ctx->map_image = NULL;
	ctx->minimap_image = NULL;
	ctx->background_image = NULL;
	ctx->action_image = NULL;
	ctx->north = NULL;
	ctx->south = NULL;
	ctx->east = NULL;
	ctx->west = NULL;
	ctx->door = NULL;
	ctx->anim = NULL;
	ctx->anim_frame = 7;
}

static int	cub_init_player(t_ctx *ctx)
{
	ctx->player = ft_calloc(1, sizeof(t_player));
	if (!ctx->player)
	{
		ft_dprintf(2, "Error: cannot initialize player.\n");
		return (1);
	}
	ctx->player->angle = 45 * PI / 180;
	ctx->player->delta_x = cos(ctx->player->angle) * 2;
	ctx->player->delta_y = sin(ctx->player->angle) * 2;
	ctx->player->x = 0;
	ctx->player->y = 0;
	return (0);
}

int	cub_init_ctx(t_ctx *ctx)
{
	ctx->map_width = 0;
	ctx->map_height = 0;
	ctx->floor = 0;
	ctx->ceiling = 0;
	ctx->floor_parsed = 0;
	ctx->ceiling_parsed = 0;
	ctx->prev_ray = 0;
	ctx->mlx_data = ft_calloc(1, sizeof(t_mlxx_data_addr));
	ctx->has_door = 0;
	if (!ctx->mlx_data)
	{
		ft_dprintf(2, "Error: cannot initialize mlx_data.\n");
		return (1);
	}
	if (cub_init_player(ctx))
		return (1);
	cub_init_key(ctx);
	cub_init_imgs(ctx);
	return (0);
}
