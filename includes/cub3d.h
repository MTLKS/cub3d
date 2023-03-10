/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:31:19 by maliew            #+#    #+#             */
/*   Updated: 2023/02/10 16:04:32 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <math.h>
# include <stdio.h>

# ifdef __APPLE__
#  include "../mlx/mlx.h"
#  define ANIM_SPEED 5
# else
#  include "../mlx_linux/mlx.h"
#  define ANIM_SPEED 50
# endif

// Key definition
# ifdef __APPLE__
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_W 13
#  define KEY_E 14
#  define KEY_M 46
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
#  define KEY_SHIFT 257
# else
#  define KEY_A 'a'
#  define KEY_S 's'
#  define KEY_D 'd'
#  define KEY_W 'w'
#  define KEY_E 'e'
#  define KEY_M 'm'
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65362
#  define KEY_UP 65364
#  define KEY_SHIFT 65505
# endif

# define PI 3.141592654
# define DR 0.0174533

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 512

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

typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	shift;
	int	mouse;
}	t_key;

typedef struct s_raycasting
{
	int		i;
	int		rays;
	int		mid;
	float	angle;
}	t_raycasting;

typedef struct s_ctx
{
	void				*mlx;
	void				*win;
	char				**map;
	int					map_width;
	int					map_height;
	t_mlxx_img			*img;
	t_mlxx_img			*map_image;
	t_mlxx_img			*minimap_image;
	t_mlxx_img			*background_image;
	t_mlxx_img			*action_image;
	t_mlxx_img			*north;
	t_mlxx_img			*south;
	t_mlxx_img			*east;
	t_mlxx_img			*west;
	t_mlxx_img			*door;
	t_mlxx_data_addr	*mlx_data;
	int					prev_ray;
	int					ceiling;
	int					floor;
	int					ceiling_parsed;
	int					floor_parsed;
	t_player			*player;
	t_key				key;
	t_mlxx_img			**anim;
	int					anim_frame;
	int					has_door;
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
	int		is_door;
}	t_ray;

typedef struct s_texture
{
	int		*color;
	float	shade;
	float	y_offset;
	float	y_step;
	float	x;
	float	y;
	float	line_h;
	float	line_o;
}	t_texture;

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
void			cub_free_2d_array(char **array, int row);
void			cub_free_2d_nt_array(char **array);
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
void			mlxx_rotate_img(void *mlx, t_mlxx_img **img, int degree);
t_mlxx_img		*mlxx_new_rect(t_ctx *ctx, int width, int height, int color);
int				*get_texture(t_ctx *ctx, char side);
int				shade(int color, float shade);

// Struct handling

int				cub_init_ctx(t_ctx *ctx);
void			cub_free_and_exit(t_ctx *ctx);

// Map parsing

int				cub_check_struct(t_ctx *ctx);
int				cub_parse_elements(t_ctx *ctx, t_list **buffer, t_list *end);
int				cub_parse_map_file(t_ctx *ctx, char *path);
int				cub_check_digit(char *color);

// Color Utils

int				cub_create_trgb(int t, int r, int g, int b);
unsigned char	cub_get_t(int trgb);
unsigned char	cub_get_r(int trgb);
unsigned char	cub_get_g(int trgb);
unsigned char	cub_get_b(int trgb);

// Hooks

int				keydown_hook(int keycode, t_ctx *ctx);
int				keyup_hook(int keycode, t_ctx *ctx);
int				mouse_hook(int x, int y, t_ctx *ctx);
int				mouse_up_hook(int button, int x, int y, t_ctx *ctx);
int				interact_hook(int keycode, t_ctx *ctx);
int				render(t_ctx *ctx);
void			door_handler(t_ctx *ctx);

// Drawing

void			put_pixel(t_ctx *ctx, int x, int y, int color);
void			cast_rays(t_ctx *ctx);
void			draw_scene(t_ctx *ctx, t_ray final_ray, float ray_angle,
					int deg);
void			create_background_image(t_ctx *ctx);
int				ray_hit(t_ctx *ctx, int pos, t_ray *ray);
void			set_v_texture(t_ray *v_ray);
void			set_h_texture(t_ray *h_ray);

// Minimap

int				generate_map_image(t_ctx *ctx);
int				generate_minimap_image(t_ctx *ctx);

// Movement

void			move_player(t_ctx *ctx);

// Animation

int				load_animation(t_ctx *ctx);
t_mlxx_img		*get_animation_frame(t_ctx *ctx);

#endif