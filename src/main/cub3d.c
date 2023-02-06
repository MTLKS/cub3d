/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:31:46 by maliew            #+#    #+#             */
/*   Updated: 2023/02/06 18:40:18 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc != 2)
	{
		ft_dprintf(2, "./cub3d <map.cub>\n");
		return (0);
	}
	ctx.mlx = mlx_init();
	ctx.win = mlx_new_window(ctx.mlx, 1024, 512, "cub3d");
	cub_init_ctx(&ctx);
	if (cub_parse_map_file(&ctx, argv[1]))
	{
		ft_dprintf(2, "Error\n");
		exit(1);
	}
	generate_map_image(&ctx);
	create_background_image(&ctx);
	load_animation(&ctx);
	mlx_loop_hook(ctx.mlx, render, &ctx);
	mlx_hook(ctx.win, 2, 1L << 0, keydown_hook, &ctx);
	mlx_hook(ctx.win, 3, 1L << 1, keyup_hook, &ctx);
	mlx_hook(ctx.win, 5, 1L << 3, mouse_up_hook, &ctx);
	mlx_hook(ctx.win, 6, 1L << 6, mouse_hook, &ctx);
	mlx_loop(ctx.mlx);
	return (0);
}
