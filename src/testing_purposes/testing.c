#include "cub3d.h"

// int	key_hook(int keycode, t_ctx *ctx)
// {
// 	(void)ctx;
// 	if (keycode == KEY_ESC)
// 	{
// 		ft_printf("ESC pressed.\n");
// 		system("leaks -q cub3d");
// 		exit(0);
// 	}
// 	return (0);
// }

// int	loop_hook(t_ctx *ctx)
// {
// 	t_mlxx_img	*ceiling;
// 	t_mlxx_img	*floor;
// 	t_mlxx_img	*buffer;

// 	buffer = mlxx_new_img(ctx->mlx, 384, 64);
// 	if (ctx->north)
// 		mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->north->img, 0, 0);
// 	if (ctx->south)
// 		mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->south->img, 64, 0);
// 	if (ctx->east)
// 		mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->east->img, 128, 0);
// 	if (ctx->west)
// 		mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->west->img, 192, 0);
// 	ceiling = square(ctx, ctx->ceiling);
// 	mlx_put_image_to_window(ctx->mlx, ctx->win, ceiling->img, 256, 0);
// 	floor = square(ctx, ctx->floor);
// 	mlx_put_image_to_window(ctx->mlx, ctx->win, floor->img, 320, 0);
// 	(void)buffer;
// 	return (0);
// }

/**
 * @brief Create a square fill with a certain color.
*/
t_mlxx_img *square(t_ctx *ctx, int color)
{
	t_mlxx_img			*img;
	t_mlxx_data_addr	addr;
	int					i;
	int					j;


	img = mlxx_new_img(ctx->mlx, 64, 64);
	addr.address = mlx_get_data_addr(img->img, &addr.pixel_bits, &addr.size_line, &addr.endian);
	j = -1;
	while (++j < 64)
	{
		i = -1;
		while (++i < 64)
		{
			addr.pixel = (j * addr.size_line) + (i * 4);
			addr.address[addr.pixel + 0] = cub_get_b(color);
			addr.address[addr.pixel + 1] = cub_get_g(color);
			addr.address[addr.pixel + 2] = cub_get_r(color);
			addr.address[addr.pixel + 3] = cub_get_t(color);
		}
	}
	return (img);
}


/**
 * @brief Draws a temporary map
 * 
 * @param ctx 
 */
void	draw_map(t_ctx *ctx)
{
	int			x;
	int			y;
	int			square_size;
	t_square	square;
	
	y = -1;
	square_size = 64;
	while (++y < ctx->map_height)
	{
		x = -1;
		while (++x < ctx->map_width)
		{
			square.x = x * square_size;
			square.y = y * square_size;
			square.size = square_size;
			if (ctx->map[y][x] == '1')
				draw_square(ctx, square, 0x00FFFFFF);
			else
				draw_square(ctx, square, 0x00000000);
		}
	}
}

/**
 * @brief Draws a THICC line from point A to point B
 * 
 * @param ctx 
 * @param startX x1
 * @param startY y1
 * @param endX x2
 * @param endY y2
 * @param color Color to draw the line in
 */
void	draw_thick_line(t_ctx *ctx, float startX, float startY, float endX, float endY, int color)
{
	float	delta_x;
	float	delta_y;
	int		dist;
	int		i;

	delta_x = endX - startX;
	delta_y = endY - startY;
	dist = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= dist;
	delta_y /= dist;
	while (dist)
	{
		i = -1;
		while (++i < 8)
			put_pixel(ctx, startX + i, startY, color);
		startX += delta_x;
		startY += delta_y;
		--dist;
	}
}
