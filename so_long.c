/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 15:54:14 by mforstho      #+#    #+#                 */
/*   Updated: 2022/07/04 16:27:06 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 256
#define HEIGHT 256

// typedef struct mlx
// {
// 	void	*window;
// 	void	*context;
// 	int32_t	width;
// 	int32_t	height;
// 	double	data_time;
// }	mlx_t;

// int32_t	main(void) // simple window
// {
// 	mlx_t	*mlx;

// 	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
// 	if (!mlx)
// 		exit(EXIT_FAILURE);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

// static mlx_image_t	*g_img;

// int32_t	main(void) // single pixel
// {
// 	mlx_t	*mlx;

// 	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
// 	if (!mlx)
// 		exit(EXIT_FAILURE);
// 	g_img = mlx_new_image(mlx, 128, 128);
// 	mlx_image_to_window(mlx, g_img, 0, 0);
// 	mlx_put_pixel(g_img, 64, 64, 0xFFFFFFFF);
// 	mlx_loop(mlx);
// 	mlx_delete_image(mlx, g_img);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

// int32_t	main(void) // image
// {
// 	mlx_t	*mlx;

// 	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
// 	if (!mlx)
// 		exit(EXIT_FAILURE);
// 	g_img = mlx_new_image(mlx, 128, 128);
// 	mlx_image_to_window(mlx, g_img, 0, 0);
// 	mlx_loop(mlx);
// 	mlx_delete_image(mlx, g_img);
// 	mlx_terminate(mlx);
// }

typedef struct	s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_data;

void	image_hook(mlx_t *mlx, mlx_image_t *image)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, image);
	// for (int x = 0; x < image->width; x++)
	// 	for (int y= 0; y < image->height; y++)
	// 		mlx_put_pixel(image, x, y, rand() % RAND_MAX);
}

void	input_hook(mlx_t *mlx, mlx_image_t *image)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

void	hook(void *param)
{
	t_data		*data;
	mlx_t		*mlx;
	mlx_image_t	*image;

	data = param;
	mlx = data->mlx;
	image = data->image;
	image_hook(mlx, image);
	input_hook(mlx, image);
}

int32_t	main(void)
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	const uint32_t	xy[2] = {0, 0};
	const uint32_t	wh[2] = {256, 256};
	t_data			data;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	texture = mlx_load_png("grass.png");
	image = mlx_texture_area_to_image(mlx, texture, xy, wh);
	mlx_image_to_window(mlx, image, 0, 0);
	data.mlx = mlx;
	data.image = image;
	mlx_loop_hook(mlx, &hook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
