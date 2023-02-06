/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:59:03 by maliew            #+#    #+#             */
/*   Updated: 2023/02/06 16:20:57 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Stores color information into the context struct.
 * 
 * @param ctx Context struct
 * @param id Type identifier
 * @param color Color string eg. 255,255,255
 * 
 * @return 0 if parsed, 1 if not parsed
*/
static int	cub_store_element_color(t_ctx *ctx, char *id, char *color)
{
	int		i;
	char	**colors_split;
	int		colors[3];

	colors_split = ft_split(color, ',');
	if (cub_2darray_count_row(colors_split) != 3)
		return (1);
	i = -1;
	while (colors_split[++i])
		colors[i] = ft_atoi(colors_split[i]);
	if (ft_strncmp(id, "F", 2) == 0 && ctx->floor_parsed == 0)
		ctx->floor = cub_create_trgb(0, colors[0], colors[1], colors[2]);
	else if (ft_strncmp(id, "C", 2) == 0 && ctx->ceiling_parsed == 0)
		ctx->ceiling = cub_create_trgb(0, colors[0], colors[1], colors[2]);
	else
		return (1);
	return (0);
}

/**
 * @brief Stores sprite image into the context struct.
 * 
 * @param ctx Context struct
 * @param id Type identifier
 * @param path Filepath to image
 * 
 * @return 0 if parsed, 1 if error
*/
static int	cub_store_element_img(t_ctx *ctx, char *id, char *path)
{
	if (ft_strncmp(id, "NO", 3) == 0 && ctx->north == NULL)
		ctx->north = mlxx_xpm_file_to_img(ctx->mlx, path);
	else if (ft_strncmp(id, "SO", 3) == 0 && ctx->south == NULL)
		ctx->south = mlxx_xpm_file_to_img(ctx->mlx, path);
	else if (ft_strncmp(id, "EA", 3) == 0 && ctx->east == NULL)
		ctx->east = mlxx_xpm_file_to_img(ctx->mlx, path);
	else if (ft_strncmp(id, "WE", 3) == 0 && ctx->west == NULL)
		ctx->west = mlxx_xpm_file_to_img(ctx->mlx, path);
	else if (ft_strncmp(id, "DO", 3) == 0 && ctx->door == NULL)
		ctx->door = mlxx_xpm_file_to_img(ctx->mlx, path);
	else
		return (1);
	return (0);
}

/**
 * @brief Takes in a line of information and parses it into context struct.
 * 
 * @param ctx Context struct
 * @param line Line of information eg. NO /path/to/file.xpm
 * 
 * @return 0 if parsed, 1 if error
*/
static int	cub_parse_element(t_ctx *ctx, char *line)
{
	char	**array;

	array = ft_split(line, ' ');
	if (cub_2darray_count_row(array) != 2)
		return (1);
	if (cub_store_element_img(ctx, array[0], array[1])
		&& cub_store_element_color(ctx, array[0], array[1]))
		return (1);
	if (ft_strncmp(array[0], "F", 2) == 0 && ctx->floor_parsed == 0)
		ctx->floor_parsed = 1;
	else if (ft_strncmp(array[0], "C", 2) == 0 && ctx->floor_parsed == 0)
		ctx->ceiling_parsed = 1;
	return (0);
}

/**
 * @brief Runs through linked list of buffer lines and parse the elements.
 * Sets the head of linked list buffer to the next node if no error.
 * 
 * @param ctx Context struct
 * @param buffer Linked list of get_next_line buffers.
 * 
 * @return 0 when all elements are parsed, 1 if error
*/
int	cub_parse_elements(t_ctx *ctx, t_list **buffer)
{
	t_list	*temp;
	char	*line;

	while ((*buffer)->next
		&& !(ctx->north && ctx->south && ctx->east && ctx->west
			&& ctx->door && ctx->floor_parsed && ctx->ceiling_parsed))
	{
		line = (*buffer)->content;
		if (*line != '\0' && cub_parse_element(ctx, line))
			return (1);
		temp = *buffer;
		*buffer = (*buffer)->next;
		ft_lstdelone(temp, &free);
	}
	return (0);
}
