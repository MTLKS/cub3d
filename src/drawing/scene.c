/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:48:56 by echai             #+#    #+#             */
/*   Updated: 2023/02/01 18:15:21 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_texture(t_ctx *ctx, t_texture *texture, float deg)
{
	int		y;
	int		*color;
	float	shades;

	y = -1;
	color = texture->color;
	shades = texture->shade;
	while (++y < texture->line_h)
	{
		put_pixel(ctx, deg, (y + texture->line_o),
			shade(color[(int)texture->x + ((int)texture->y * 64)], shades));
		texture->y += texture->y_step;
	}
}

void	get_texture_offset(t_ctx *ctx, t_texture *text, t_ray ray, float angle)
{
	text->y = text->y_offset * text->y_step;
	if (ray.shade == 1)
	{
		text->x = (int)(ray.x) % 64;
		if (rad_to_deg(angle) < 180)
			text->x = 63 - text->x;
	}
	else
	{
		text->x = (int)(ray.y) % 64;
		if (rad_to_deg(angle) < 90 || rad_to_deg(angle) > 270)
			text->x = 63 - text->x;
	}
	text->color = get_texture(ctx, ray.side);
	text->shade = ray.shade;
}

/**
 * @brief Draws the scene out
 * Assumed that screen height is 320px
 * Texture width & height is 64
 * 
 * @param ctx 
 * @param final_ray 
 * @param ray_angle 
 * @param deg 
 */
void	draw_scene(t_ctx *ctx, t_ray final_ray, float ray_angle, int deg)
{
	float		ray_dist;
	float		line_h;
	float		line_o;
	t_texture	texture;

	ray_dist = final_ray.dist * cos(rad_limit(ctx->player->angle - ray_angle));
	line_h = (64 * ctx->img->height) / ray_dist;
	texture.y_step = 64.0 / line_h;
	texture.y_offset = 0;
	if (line_h > ctx->img->height)
	{
		texture.y_offset = (line_h - ctx->img->height) / 2.0;
		line_h = ctx->img->height;
	}
	line_o = (ctx->img->height / 2) - (line_h / 2);
	get_texture_offset(ctx, &texture, final_ray, ray_angle);
	texture.line_h = line_h;
	texture.line_o = line_o;
	draw_texture(ctx, &texture, deg);
}
