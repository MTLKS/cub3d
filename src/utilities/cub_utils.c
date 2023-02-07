/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:43:20 by maliew            #+#    #+#             */
/*   Updated: 2023/02/07 18:39:28 by maliew           ###   ########.fr       */
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

void	cub_free_2d_array(char **array, int row)
{
	int	i;

	i = -1;
	while (++i < row)
		free(array[i]);
	free(array);
}

void	cub_free_2d_nt_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
