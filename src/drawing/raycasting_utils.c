/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:45:21 by echai             #+#    #+#             */
/*   Updated: 2023/02/06 17:58:01 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ray_hit(t_ctx *ctx, int pos, t_ray *ray)
{
	int	hit;

	hit = (pos > 0 && pos < (ctx->map_height * ctx->map_width)
			&& ft_strchr("12", ctx->map[pos / ctx->map_width]
			[pos % ctx->map_width]) != 0);
	if (hit && ft_strchr("2", ctx->map[pos / ctx->map_width]
			[pos % ctx->map_width]) != 0)
		ray->is_door = 1;
	return (hit);
}

void	set_v_texture(t_ray *v_ray)
{
	if (v_ray->is_door)
	{
		v_ray->side = 'D';
		return ;
	}
	v_ray->side = 'E';
	if (v_ray->deg > 90 && v_ray->deg < 270)
		v_ray->side = 'W';
}

void	set_h_texture(t_ray *h_ray)
{
	if (h_ray->is_door)
	{
		h_ray->side = 'D';
		return ;
	}
	h_ray->side = 'N';
	if (h_ray->deg > 0 && h_ray->deg < 180)
		h_ray->side = 'S';
}
