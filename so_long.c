/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 15:54:14 by mforstho      #+#    #+#                 */
/*   Updated: 2022/07/05 15:59:59 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 256
#define HEIGHT 256

typedef struct s_player
{
	int			x;
	int			y;
	int			health;
}	t_player;

typedef struct	s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_player	player;
}	t_data;

void	image_hook(mlx_t *mlx, mlx_image_t *image)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, image);
}

void	input_hook(mlx_t *mlx, mlx_image_t *image)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
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
	uint32_t		xy[2];
	uint32_t		wh[2];
	t_data			data;

	xy[0] = 16 * 5 * 8;
	xy[1] = 16 * 15 * 5 - 8;
	wh[0] = 16 * 5;
	wh[1] = 16 * 5;
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	texture = mlx_load_png("dungeonTileset.png");
	image = mlx_texture_area_to_image(mlx, texture, xy, wh);
	mlx_image_to_window(mlx, image, 0, 0);
	data.mlx = mlx;
	data.image = image;
	mlx_loop_hook(mlx, &hook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
