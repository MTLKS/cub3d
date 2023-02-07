/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_free_and_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:13:47 by maliew            #+#    #+#             */
/*   Updated: 2023/02/07 21:19:00 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_free_imgs(t_ctx *ctx)
{
	if (ctx->img != NULL)
		mlxx_destroy_img(ctx->mlx, ctx->img);
	if (ctx->map_image != NULL)
		mlxx_destroy_img(ctx->mlx, ctx->map_image);
	if (ctx->minimap_image != NULL)
		mlxx_destroy_img(ctx->mlx, ctx->minimap_image);
	if (ctx->background_image != NULL)
		mlxx_destroy_img(ctx->mlx, ctx->background_image);
	if (ctx->action_image != NULL)
		mlxx_destroy_img(ctx->mlx, ctx->action_image);
	if (ctx->north != NULL)
		mlxx_destroy_img(ctx->mlx, ctx->north);
	if (ctx->south != NULL)
		mlxx_destroy_img(ctx->mlx, ctx->south);
	if (ctx->east != NULL)
		mlxx_destroy_img(ctx->mlx, ctx->east);
	if (ctx->west != NULL)
		mlxx_destroy_img(ctx->mlx, ctx->west);
	if (ctx->door != NULL)
		mlxx_destroy_img(ctx->mlx, ctx->door);
}

static void	cub_free_anim(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < 8)
		mlxx_destroy_img(ctx->mlx, ctx->anim[i]);
	free(ctx->anim);
}

void	cub_free_and_exit(t_ctx *ctx)
{
	mlx_destroy_window(ctx->mlx, ctx->win);
	cub_free_imgs(ctx);
	cub_free_anim(ctx);
	free(ctx->player);
	free(ctx->mlx_data);
	cub_free_2d_array(ctx->map, ctx->map_height);
	exit(0);
}
