/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:13:20 by maliew            #+#    #+#             */
/*   Updated: 2023/02/07 18:04:06 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Get the vertical slice object
 * 
 * @param ctx 
 * @param side 
 * @return int* 
 */
int	*get_texture(t_ctx *ctx, char side)
{
	t_mlxx_img	*img;
	int			*data;
	int			bpp;
	int			size;
	int			endian;

	img = NULL;
	if (side == 'N')
		img = ctx->north;
	else if (side == 'S')
		img = ctx->south;
	else if (side == 'E')
		img = ctx->east;
	else if (side == 'W')
		img = ctx->west;
	else if (side == 'D')
		img = ctx->door;
	data = (int *)mlx_get_data_addr(img->img, &bpp, &size, &endian);
	return (data);
}

int	shade(int color, float shade)
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	t = (((unsigned char *)&color)[3]);
	r = (((unsigned char *)&color)[2]);
	g = (((unsigned char *)&color)[1]);
	b = (((unsigned char *)&color)[0]);
	r *= shade;
	g *= shade;
	b *= shade;
	return (cub_create_trgb(t, r, g, b));
}
