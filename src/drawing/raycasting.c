/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:29:31 by echai             #+#    #+#             */
/*   Updated: 2023/02/06 17:58:35 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Find where the ray hits a wall
 * 
 * @param ctx 
 * @param temp 
 * @param ray 
 * @param dof 
 */
void	find_ray_end(t_ctx *ctx, t_temp temp, t_ray *ray, int dof)
{
	int		depth_of_field;
	int		map_x;
	int		map_y;
	int		pos;

	depth_of_field = -1;
	while (++depth_of_field < dof)
	{
		map_x = (int)(temp.ray_x) >> 6;
		map_y = (int)(temp.ray_y) >> 6;
		pos = map_y * ctx->map_width + map_x;
		if (ray_hit(ctx, pos, ray))
		{
			ray->x = temp.ray_x;
			ray->y = temp.ray_y;
			ray->dist = dist(ctx->player->x, ctx->player->y,
					ray->x, ray->y);
			depth_of_field = dof;
		}
		else
		{
			temp.ray_x += temp.x_offset;
			temp.ray_y += temp.y_offset;
		}
	}
}

/**
 * @brief Checks horizontal ray
 * 
 * @param ctx 
 * @param ray 
 * @param temp temp struct for calculations
 * @param dof max depth of field
 * @return t_ray 
 */
void	check_hray(t_ctx *ctx, t_ray *ray, t_temp t, int dof)
{
	ray->x = ctx->player->x;
	ray->y = ctx->player->y;
	ray->dist = 1000000;
	ray->deg = rad_to_deg(t.ray_angle);
	if (t.ray_angle > PI)
	{
		t.ray_y = (((int)ctx->player->y >> 6) << 6) - 0.0001;
		t.ray_x = (ctx->player->y - t.ray_y) * t.tan_multip + ctx->player->x;
		t.y_offset = -64;
		t.x_offset = t.y_offset * -1 * t.tan_multip;
	}
	if (t.ray_angle < PI)
	{
		t.ray_y = (((int)ctx->player->y >> 6) << 6) + 64;
		t.ray_x = (ctx->player->y - t.ray_y) * t.tan_multip + ctx->player->x;
		t.y_offset = 64;
		t.x_offset = t.y_offset * -1 * t.tan_multip;
	}
	if (t.ray_angle == 0 || t.ray_angle == PI)
	{
		t.ray_x = ctx->player->x;
		t.ray_y = ctx->player->y;
		return ;
	}
	find_ray_end(ctx, t, ray, dof);
}

/**
 * @brief Checks vertical ray
 * 
 * @param ctx 
 * @param ray 
 * @param temp temp struct for calculations
 * @param dof max depth of field
 * @return t_ray 
 */
void	check_vray(t_ctx *ctx, t_ray *ray, t_temp t, int dof)
{
	ray->x = ctx->player->x;
	ray->y = ctx->player->y;
	ray->dist = 1000000;
	ray->deg = rad_to_deg(t.ray_angle);
	if (t.ray_angle > PI / 2 && t.ray_angle < 3 * PI / 2)
	{
		t.ray_x = (((int)ctx->player->x >> 6) << 6) - 0.0001;
		t.ray_y = (ctx->player->x - t.ray_x) * t.tan_multip + ctx->player->y;
		t.x_offset = -64;
		t.y_offset = t.x_offset * -1 * t.tan_multip;
	}
	if (t.ray_angle < PI / 2 || t.ray_angle > 3 * PI / 2)
	{
		t.ray_x = (((int)ctx->player->x >> 6) << 6) + 64;
		t.ray_y = (ctx->player->x - t.ray_x) * t.tan_multip + ctx->player->y;
		t.x_offset = 64;
		t.y_offset = t.x_offset * -1 * t.tan_multip;
	}
	if (t.ray_angle == PI / 2 || t.ray_angle == 3 * PI / 2)
	{
		t.ray_x = ctx->player->x;
		t.ray_y = ctx->player->y;
		return ;
	}
	find_ray_end(ctx, t, ray, dof);
}

/**
 * @brief Get the ray that needs to be drawn
 * 
 * @param ctx 
 * @param v_ray 
 * @param h_ray 
 * @return t_ray 
 */
t_ray	get_ray(t_ctx *ctx, t_ray v_ray, t_ray h_ray)
{
	if ((v_ray.dist == h_ray.dist && ctx->prev_ray) || v_ray.dist < h_ray.dist)
	{
		ctx->prev_ray = 1;
		v_ray.shade = 0.8;
		set_v_texture(&v_ray);
		return (v_ray);
	}
	ctx->prev_ray = 0;
	h_ray.shade = 1;
	set_h_texture(&h_ray);
	return (h_ray);
}

/**
 * @brief Cast rays
 * 
 * @param ctx 
 */
void	cast_rays(t_ctx *ctx)
{
	t_raycasting	rc;
	t_ray			h_ray;
	t_ray			v_ray;
	t_ray			final_ray;
	t_temp			temp;

	rc.rays = ctx->img->width;
	rc.mid = rc.rays / 2;
	rc.angle = 60.0 / (float)rc.rays;
	temp.ray_angle = rad_limit(ctx->player->angle
			- deg_to_rad(rc.mid * rc.angle));
	rc.i = -1;
	while (++rc.i < rc.rays)
	{
		h_ray.is_door = 0;
		v_ray.is_door = 0;
		temp.tan_multip = -1 / tan(temp.ray_angle);
		check_hray(ctx, &h_ray, temp, 24);
		temp.tan_multip = -tan(temp.ray_angle);
		check_vray(ctx, &v_ray, temp, 24);
		final_ray = get_ray(ctx, v_ray, h_ray);
		draw_scene(ctx, final_ray, temp.ray_angle, rc.i);
		temp.ray_angle = rad_limit(temp.ray_angle + deg_to_rad(rc.angle));
	}
}
