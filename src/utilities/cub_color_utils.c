/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:13:20 by maliew            #+#    #+#             */
/*   Updated: 2022/12/31 11:16:36 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned char	cub_get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	cub_get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	cub_get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	cub_get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}
