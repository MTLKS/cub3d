/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:23:16 by maliew            #+#    #+#             */
/*   Updated: 2023/02/06 18:47:03 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_animation(t_ctx *ctx)
{
	int	i;

	ctx->anim = malloc(8 * sizeof(t_mlxx_img *));
	ctx->anim[0] = mlxx_xpm_file_to_img(ctx->mlx, "assets/anim/00.xpm");
	ctx->anim[1] = mlxx_xpm_file_to_img(ctx->mlx, "assets/anim/01.xpm");
	ctx->anim[2] = mlxx_xpm_file_to_img(ctx->mlx, "assets/anim/02.xpm");
	ctx->anim[3] = mlxx_xpm_file_to_img(ctx->mlx, "assets/anim/03.xpm");
	ctx->anim[4] = mlxx_xpm_file_to_img(ctx->mlx, "assets/anim/04.xpm");
	ctx->anim[5] = mlxx_xpm_file_to_img(ctx->mlx, "assets/anim/05.xpm");
	ctx->anim[6] = mlxx_xpm_file_to_img(ctx->mlx, "assets/anim/06.xpm");
	ctx->anim[7] = mlxx_xpm_file_to_img(ctx->mlx, "assets/anim/07.xpm");
	i = -1;
	while (++i < 8)
	{
		if (ctx->anim[i] == NULL)
			return (1);
	}
	return (0);
}

t_mlxx_img	*get_animation_frame(t_ctx *ctx)
{
	static int	count = 0;

	++count;
	if (count % ANIM_SPEED == 0)
	{
		if (ctx->anim_frame < 7)
			ctx->anim_frame++;
	}
	return (ctx->anim[ctx->anim_frame]);
}
