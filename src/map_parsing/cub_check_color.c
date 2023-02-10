/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:58:05 by maliew            #+#    #+#             */
/*   Updated: 2023/02/10 16:07:44 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_check_color(int colors[3])
{
	(void)colors;
	return (0);
}

int	cub_check_digit(char *color)
{
	int	i;

	i = -1;
	while (color[++i])
	{
		if (!ft_isdigit(color[i]) && color[i] != ',')
			return (1);
	}
	return (0);
}
