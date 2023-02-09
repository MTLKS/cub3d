/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_map_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:42:33 by maliew            #+#    #+#             */
/*   Updated: 2023/02/09 18:09:11 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Parse map into 2d array in context struct.
 * 
 * @param ctx Context struct
 * @param buffer Linked list of get_next_line buffers.
 * 
 * @return 0
*/
static int	cub_parse_map(t_ctx *ctx, t_list *buffer)
{
	t_list	*temp;
	int		i;

	while (buffer && buffer->content && *(char *)(buffer->content) == 0)
		buffer = buffer->next;
	temp = buffer;
	while (temp)
	{
		if (ctx->map_width < (int)ft_strlen(temp->content))
			ctx->map_width = (int)ft_strlen(temp->content);
		ctx->map_height++;
		temp = temp->next;
	}
	ctx->map = (char **)ft_calloc(ctx->map_height, sizeof(char *));
	temp = buffer;
	i = 0;
	while (temp)
	{
		ctx->map[i] = (char *)ft_calloc(ctx->map_width, sizeof(char));
		ft_strlcpy(ctx->map[i++], temp->content, ctx->map_width + 1);
		temp = temp->next;
	}
	return (0);
}

/**
 * @brief Checks map file for extension and opens it.
 * 
 * @param path Filepath
 * 
 * @return fd of file opened, -1 if error
*/
static int	cub_open_map_fd(char *path)
{
	char	*temp;
	int		fd;

	temp = ft_substr(path, ft_strlen(path) - 4, 4);
	if (ft_strncmp(temp, ".cub", 4) != 0)
	{
		free(temp);
		ft_dprintf(2, "Error: wrong extension.\n");
		return (-1);
	}
	free(temp);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_dprintf(2, "Error: cannot open map file.\n");
	return (fd);
}

/**
 * @brief Parses buffer lines into context struct, then frees the buffer.
 * 
 * @param ctx Context struct
 * @param map_buffer Linked list of get_next_line buffers.
 * 
 * @return 0 if parsed, 1 if error.
*/
static int	cub_parse_struct(t_ctx *ctx, t_list **map_buffer)
{
	int		status;
	t_list	*map;
	t_list	*temp;

	temp = *map_buffer;
	while (temp)
	{
		if (*(char *)(temp)->content == '\0')
			map = temp;
		temp = temp->next;
	}
	status = (cub_parse_elements(ctx, map_buffer, map)
			|| cub_parse_map(ctx, map)
			|| cub_check_struct(ctx));
	ft_lstclear(map_buffer, &free);
	return (status);
}

/**
 * @brief Opens map file and parses in into context struct, and then run checks.
 * 
 * @param ctx Context struct
 * @param path Path to .cub file
 * 
 * @return 0 if ok, >1 if error
*/
int	cub_parse_map_file(t_ctx *ctx, char *path)
{
	int		fd;
	char	*buffer;
	char	*temp;
	t_list	*map_buffer;

	fd = cub_open_map_fd(path);
	if (fd == -1)
		return (1);
	map_buffer = NULL;
	buffer = get_next_line(fd);
	if (buffer == NULL)
		return (ft_dprintf(2, "Error: empty map file.\n"));
	while (buffer)
	{
		temp = ft_strtrim(buffer, "\n");
		ft_lstadd_back(&map_buffer, ft_lstnew(temp));
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (cub_parse_struct(ctx, &map_buffer));
}
