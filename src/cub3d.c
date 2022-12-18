/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:31:46 by maliew            #+#    #+#             */
/*   Updated: 2022/12/18 12:40:19 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_ctx	ctx;
	
	(void)argc;
	(void)argv;
	ctx.mlx = mlx_init();
	ctx.win = mlx_new_window(ctx.mlx, 1280, 720, "cub3d");
	return (0);
}
