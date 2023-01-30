/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:31:46 by maliew            #+#    #+#             */
/*   Updated: 2023/01/30 13:51:08 by echai            ###   ########.fr       */
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
	cub_init_ctx(&ctx);
	ctx.mlx = mlx_init();
	ctx.win = mlx_new_window(ctx.mlx, 1024, 512, "cub3d");
	if (cub_parse_map_file(&ctx, argv[1]))
	{
		ft_dprintf(2, "Error\n");
		exit(1);
	}
	// for (int i = 0; i < ctx.map_height; i++)
	// {
	// 	for (int j = 0; j < ctx.map_width; j++)
	// 		ft_printf("%c", ctx.map[i][j]);
	// 	ft_printf("\n");
	// }
	// ft_printf("%d %d\n", ctx.map_width, ctx.map_height);
	// ft_printf("%X %X\n", ctx.floor, ctx.ceiling);
	// ft_printf("%p %p %p %p\n", ctx.north, ctx.south, ctx.east, ctx.west);
	mlx_do_key_autorepeaton(ctx.mlx);
	mlx_loop_hook(ctx.mlx, render, &ctx);
	mlx_hook(ctx.win, 2, 1L << 0, key_hook, &ctx);
	mlx_loop(ctx.mlx);
	return (0);
}
