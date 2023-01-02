/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:31:19 by maliew            #+#    #+#             */
/*   Updated: 2023/01/02 17:31:23 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

// Key definition
# ifdef __APPLE__
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_W 13
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
# else
#  define KEY_A 'a'
#  define KEY_S 's'
#  define KEY_D 'd'
#  define KEY_W 'w'
#  define KEY_ESC 65307
#  define KEY_LEFT 65363
#  define KEY_RIGHT 65361
#  define KEY_DOWN 65362
#  define KEY_UP 65364
# endif

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
	char		**map;
	int			map_width;
	int			map_height;
	t_mlxx_img	*north;
	t_mlxx_img	*south;
	t_mlxx_img	*east;
	t_mlxx_img	*west;
	int			ceiling;
	int			floor;
	int			ceiling_parsed;
	int			floor_parsed;
}	t_ctx;


// Utils

int				cub_2darray_count_row(char **array);

// Image handling

t_mlxx_img		*mlxx_new_img(void *mlx, int width, int height);
t_mlxx_img		*mlxx_xpm_file_to_img(void *mlx, char *path);
void			mlxx_destroy_img(void *mlx, t_mlxx_img *img);
void			mlxx_copy_image(t_mlxx_img *des, t_mlxx_img *src, int x, int y);
void			mlxx_copy_pixel(t_mlxx_data_addr d, t_mlxx_data_addr s);

// Struct handling

void			cub_init_ctx(t_ctx *ctx);

// Map parsing

int				cub_check_struct(t_ctx *ctx);
int				cub_parse_elements(t_ctx *ctx, t_list **buffer);
int				cub_parse_map_file(t_ctx *ctx, char *path);

// Color Utils

int				cub_create_trgb(int t, int r, int g, int b);
unsigned char	cub_get_t(int trgb);
unsigned char	cub_get_r(int trgb);
unsigned char	cub_get_g(int trgb);
unsigned char	cub_get_b(int trgb);

// Testing purposes

t_mlxx_img		*square(t_ctx *ctx, int color);
int				key_hook(int keycode, t_ctx *ctx);
int				loop_hook(t_ctx *ctx);

#endif