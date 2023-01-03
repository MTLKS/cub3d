/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:29:31 by echai             #+#    #+#             */
/*   Updated: 2023/01/03 15:23:12 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char world[8][8] = {
	{'1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1'},
};

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
	int		map_pos;

	depth_of_field = -1;
	while(++depth_of_field < dof) // loop straight left or right
	{
		map_x = (int)(temp.ray_x) >> 6; // divide 64
		map_y = (int)(temp.ray_y) >> 6;
		map_pos = map_y * 8 + map_x;
		if (map_pos > 0 && map_pos < 64 && world[map_y][map_x] == '1')
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
void	check_hray(t_ctx *ctx, t_ray *ray, t_temp temp, int dof)
{
	ray->x = ctx->player->x;
	ray->y = ctx->player->y;
	ray->dist = 1000000;
	if (temp.ray_angle > PI)
	{
		temp.ray_y = (((int)ctx->player->y >> 6) << 6) - 0.0001;
		temp.ray_x = (ctx->player->y - temp.ray_y) * temp.tan_multip + ctx->player->x;
		temp.y_offset = -64;
		temp.x_offset = temp.y_offset * - 1 * temp.tan_multip;
	}
	if (temp.ray_angle < PI)
	{
		temp.ray_y = (((int)ctx->player->y >> 6) << 6) + 64;
		temp.ray_x = (ctx->player->y - temp.ray_y) * temp.tan_multip + ctx->player->x;
		temp.y_offset = 64;
		temp.x_offset = temp.y_offset * - 1 * temp.tan_multip;
	}
	if (temp.ray_angle == 0 || temp.ray_angle == PI)
	{
		temp.ray_x = ctx->player->x;
		temp.ray_y = ctx->player->y;
		return ;
	}
	find_ray_end(ctx, temp, ray, dof);
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
void	check_vray(t_ctx *ctx, t_ray *ray, t_temp temp, int dof)
{
	ray->x = ctx->player->x;
	ray->y = ctx->player->y;
	ray->dist = 1000000;
	if (temp.ray_angle > PI/2 && temp.ray_angle < 3*PI/2) // look left
	{
		temp.ray_x = (((int)ctx->player->x >> 6) << 6) - 0.0001;
		temp.ray_y = (ctx->player->x - temp.ray_x) * temp.tan_multip + ctx->player->y;
		temp.x_offset = -64;
		temp.y_offset = temp.x_offset * - 1* temp.tan_multip;
	}
	if (temp.ray_angle < PI/2 ||  temp.ray_angle > 3*PI/2) // look right
	{
		temp.ray_x = (((int)ctx->player->x >> 6) << 6) + 64;
		temp.ray_y = (ctx->player->x - temp.ray_x) * temp.tan_multip + ctx->player->y;
		temp.x_offset = 64;
		temp.y_offset = temp.x_offset * - 1* temp.tan_multip;
	}
	if (temp.ray_angle == PI/2 || temp.ray_angle == 3*PI/2) // loop straight up or down
	{
		temp.ray_x = ctx->player->x;
		temp.ray_y = ctx->player->y;
		return ;
	}
	find_ray_end(ctx, temp, ray, dof);
}

void	draw_rays(t_ctx *ctx)
{
	int	ray;
	t_ray	h_ray;
	t_ray	v_ray;
	t_temp	temp;
	float	ray_dist;
	int		render_color;
	t_line	line;

	temp.ray_angle = rad_limit(ctx->player->angle - deg_to_rad(30));
	ray = -1;
	while (++ray < 60)
	{
		temp.tan_multip = -1/tan(temp.ray_angle);
		check_hray(ctx, &h_ray, temp, 8);
		temp.tan_multip = -tan(temp.ray_angle);
		check_vray(ctx, &v_ray, temp, 8);
		if (v_ray.dist < h_ray.dist)
		{
			line.x2 = v_ray.x;
			line.y2 = v_ray.y;
			ray_dist = v_ray.dist;
			render_color = 0x00DD0000;
		}
		else
		{
			line.x2 = h_ray.x;
			line.y2 = h_ray.y;
			ray_dist = h_ray.dist;
			render_color = 0x00880000;
		}
		line.x1 = ctx->player->x;
		line.y1 = ctx->player->y;
		draw_line(ctx, line, 0x0011FF22);

		// Draw 3D walls
		ray_dist = ray_dist * cos(rad_limit(ctx->player->angle - temp.ray_angle));
		float line_h = (64 * 320)/ray_dist; //screen height 320px, line height
		if (line_h > 320)
			line_h = 320;
		float line_o = 160 - line_h/2; // line offset
		draw_thick_line(ctx, ray * 8 + 530, (int)line_o, ray * 8 + 530, (int)line_h + line_o, render_color);

		temp.ray_angle = rad_limit(temp.ray_angle + deg_to_rad(1));
	}
}
