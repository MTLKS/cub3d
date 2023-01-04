/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:48:56 by echai             #+#    #+#             */
/*   Updated: 2023/01/04 16:49:26 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_scene(t_ctx *ctx, t_ray final_ray, float ray_angle, int deg)
{
	float	ray_dist;
	float	line_h;
	float	line_o;

	ray_dist = final_ray.dist * cos(rad_limit(ctx->player->angle - ray_angle));
	line_h = (64 * 320) / ray_dist; //screen height 320px, line height
	if (line_h > 320)
		line_h = 320;
	line_o = 160 - line_h / 2; // line offset
	draw_thick_line(ctx, deg * 8 + 530, (int)line_o,
		deg * 8 + 530, (int)line_h + line_o, final_ray.color);
}