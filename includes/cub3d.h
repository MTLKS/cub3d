/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echai <echai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:31:19 by maliew            #+#    #+#             */
/*   Updated: 2023/01/30 17:51:55 by echai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>

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

# define PI 3.141592654
# define DR 0.0174533

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	delta_x;
	float	delta_y;
}	t_player;

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
	void				*mlx;
	void				*win;
	char				**map;
	int					map_width;
	int					map_height;
	t_mlxx_img			*img;
	t_mlxx_img			*north;
	t_mlxx_img			*south;
	t_mlxx_img			*east;
	t_mlxx_img			*west;
	// void				*test;
	t_mlxx_data_addr	*mlx_data;
	int					ceiling;
	int					floor;
	int					ceiling_parsed;
	int					floor_parsed;
	t_player			*player;
}	t_ctx;

// Drawing structs
typedef struct s_line
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;
}	t_line;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
}	t_square;

typedef struct s_ray
{
	float	x;
	float	y;
	float	dist;
	float	deg;
	float	shade;
	char	side;
}	t_ray;

// Temporary struct for ray calculation
typedef struct s_temp
{
	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	tan_multip;
	float	x_offset;
	float	y_offset;
}	t_temp;

// Utils

int				cub_2darray_count_row(char **array);
float			dist(float x1, float y1, float x2, float y2);
float			deg_to_rad(float angle);
float			rad_to_deg(float angle);
float			deg_limit(float angle);
float			rad_limit(float angle);

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
int				*get_texture(t_ctx *ctx, char side);
int				shade(int color, float shade);

t_mlxx_img		*square(t_ctx *ctx, int color);
int				loop_hook(t_ctx *ctx);

// Hooks
int				key_hook(int keycode, t_ctx *ctx);
int				render(t_ctx *ctx);

// Drawing
void			put_pixel(t_ctx *ctx, int x, int y, int color);
void			draw_square(t_ctx *ctx, t_square square, int color);
void			draw_line(t_ctx *ctx, t_line line, int color);
void			draw_player(t_ctx *ctx, int color, int size);
void			draw_map(t_ctx *ctx);
void			cast_rays(t_ctx *ctx);
void			draw_scene(t_ctx *ctx, t_ray final_ray, float ray_angle, int deg);
void			draw_thick_line(t_ctx *ctx, float startX, float startY, float endX, float endY, int color);

#endif