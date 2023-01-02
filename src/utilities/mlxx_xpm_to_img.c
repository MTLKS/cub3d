/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxx_xpm_to_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:10:47 by maliew            #+#    #+#             */
/*   Updated: 2022/12/26 21:31:16 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlxx_img	*mlxx_xpm_file_to_img(void *mlx, char *path)
{
	t_mlxx_img	*res;

	res = (t_mlxx_img *)malloc(sizeof(t_mlxx_img));
	res->img = mlx_xpm_file_to_image(mlx, path, &res->width, &res->height);
	if (res->img == NULL)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
