/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 20:29:45 by echai             #+#    #+#             */
/*   Updated: 2023/01/03 13:44:14 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Calculate distance between two points
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @return float 
 */
float	dist(float x1, float y1, float x2, float y2)
{
	float	delta_x;
	float	delta_y;
	int		dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	dist = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	return (dist);
}

/**
 * @brief Convert degree to radians
 * 
 * @param angle Angle in degrees
 * @return float 
 */
float	deg_to_rad(float angle)
{
	return (angle * PI / 180);
}

/**
 * @brief Ensure angle is within 0-360
 * 
 * @param angle 
 * @return float 
 */
float	deg_limit(float angle)
{
	if (angle > 359)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}

/**
 * @brief Ensure angle is within 0-2π
 * 
 * @param angle 
 * @return float 
 */
float	rad_limit(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}
