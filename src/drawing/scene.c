/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:48:56 by echai             #+#    #+#             */
/*   Updated: 2023/01/30 18:01:55 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_texture()
// {
// 	int		y;
// 	int		x;
// 	int		*color;

	
// }

void	draw_scene(t_ctx *ctx, t_ray final_ray, float ray_angle, int deg)
{
	float	ray_dist;
	float	line_h;
	float	line_o;
	float	ty_step;
	float	ty_offset;
	float	ty;
	float	tx;

	ray_dist = final_ray.dist * cos(rad_limit(ctx->player->angle - ray_angle));
	line_h = (64 * 320) / ray_dist; //screen height 320px, line height
	ty_step = 64.0/line_h;
	ty_offset = 0;
	if (line_h > 320)
	{
		ty_offset = (line_h - 320)/2.0;
		line_h = 320;
	}
	line_o = 160 - line_h / 2; // line offset
	int		y;
	int		x;
	int		*color;
	y = -1;
	ty = ty_offset * ty_step;
	if (final_ray.shade == 1)
	{
		tx = (int)(final_ray.x) % 64;
		if (rad_to_deg(ray_angle) < 180)
			tx = 63 - tx;
	}
	else
	{
		tx = (int)(final_ray.y) % 64;
		if (rad_to_deg(ray_angle) < 90 || rad_to_deg(ray_angle) > 270)
			tx = 63 - tx;
	}
	color = get_texture(ctx, final_ray.side);
	// color = get_texture(ctx, 'W');
	while (++y < line_h)
	{
		x = -1;
		while (++x < 8)
			put_pixel(ctx, (deg * 8 + 530) + x, (y + line_o), shade(color[(int)tx + ((int)ty * 64)], final_ray.shade));
		ty += ty_step;
	}
}