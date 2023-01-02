/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:43:20 by maliew            #+#    #+#             */
/*   Updated: 2023/01/02 17:12:18 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Counts the rows in a 2d array.
 * 
 * @param array 2d array.
 * 
 * @return Number of rows in 2d array.
*/
int	cub_2darray_count_row(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
