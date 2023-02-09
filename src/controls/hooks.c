/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:42:35 by echai             #+#    #+#             */
/*   Updated: 2023/02/09 18:12:53 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_action(t_ctx *ctx)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)(ctx->player->x + ctx->player->delta_x * 24) / 64;
	pos_y = (int)(ctx->player->y + ctx->player->delta_y * 24) / 64;
	if (ft_strchr("23", ctx->map[pos_y][pos_x]) != 0 && !(ft_strchr("23",
			ctx->map[((int)ctx->player->y) / 64]
			[((int)ctx->player->x) / 64]) != 0))
		mlxx_copy_image(ctx->img, ctx->action_image,
			SCREEN_WIDTH - ctx->action_image->width, 0);
}

/**
 * @brief Renders the screen at each mlx loop
 * 
 * @param ctx 
 * @return int 
 */
int	render(t_ctx *ctx)
{
	ctx->img = mlxx_new_img(ctx->mlx, 1024, 512);
	ctx->mlx_data->address = mlx_get_data_addr(ctx->img->img,
			&ctx->mlx_data->pixel_bits,
			&ctx->mlx_data->size_line, &ctx->mlx_data->endian);
	move_player(ctx);
	mlxx_copy_image(ctx->img, ctx->background_image, 0, 0);
	cast_rays(ctx);
	generate_minimap_image(ctx);
	mlxx_copy_image(ctx->img, get_animation_frame(ctx),
		SCREEN_WIDTH - get_animation_frame(ctx)->width,
		SCREEN_HEIGHT - get_animation_frame(ctx)->height);
	show_action(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img->img, 0, 0);
	mlxx_destroy_img(ctx->mlx, ctx->img);
	ctx->img = NULL;
	return (0);
}

/**
 * @brief Intermediary to handle door open key press
 * 
 * @param ctx 
 */
void	door_handler(t_ctx *ctx)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)(ctx->player->x + ctx->player->delta_x * 24) / 64;
	pos_y = (int)(ctx->player->y + ctx->player->delta_y * 24) / 64;
	if (ft_strchr("23", ctx->map[pos_y][pos_x]) != 0 && !(ft_strchr("23",
			ctx->map[((int)ctx->player->y) / 64]
			[((int)ctx->player->x) / 64]) != 0))
	{
		if (ft_strchr("2", ctx->map[pos_y][pos_x]) != 0)
			ctx->map[pos_y][pos_x] = '3';
		else if (ft_strchr("3", ctx->map[pos_y][pos_x]) != 0)
			ctx->map[pos_y][pos_x] = '2';
	}

}

int	mouse_up_hook(int button, int x, int y, t_ctx *ctx)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		door_handler(ctx);
		ctx->anim_frame = 0;
	}
	return (button);
}
