/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:31:19 by maliew            #+#    #+#             */
/*   Updated: 2022/12/18 12:38:08 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

typedef struct s_mlxx_data_addr
{
	char	*address;
	int		pixel_bits;
	int		size_line;
	int		endian;
	int		pixel;
}	t_mlxx_data_addr;

typedef struct s_mlxx_img
{
	void	*img;
	int		width;
	int		height;
}	t_mlxx_img;

typedef struct s_ctx
{
	void		*mlx;
	void		*win;
	t_mlxx_img	*north;
	t_mlxx_img	*south;
	t_mlxx_img	*east;
	t_mlxx_img	*west;

}	t_ctx;

t_mlxx_img	*mlxx_new_img(void *mlx, int width, int height);
t_mlxx_img	*mlxx_xpm_file_to_img(void *mlx, char *path);
void		mlxx_destroy_img(void *mlx, t_mlxx_img *img);
void		mlxx_copy_image(t_mlxx_img *des, t_mlxx_img *src, int x, int y);
void		mlxx_copy_pixel(t_mlxx_data_addr d, t_mlxx_data_addr s);

#endif