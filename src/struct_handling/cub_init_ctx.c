/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_ctx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:26:10 by maliew            #+#    #+#             */
/*   Updated: 2023/01/02 17:28:21 by maliew           ###   ########.fr       */
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
}
