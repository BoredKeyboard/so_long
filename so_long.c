/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 15:54:14 by mforstho      #+#    #+#                 */
/*   Updated: 2022/07/12 16:06:11 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	image_hook(mlx_t *mlx, mlx_image_t *image)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, image);
}

void	input_hook(t_data *data)
{
	const t_player	*player = &data->player;
	mlx_t			*mlx;

	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
		player->instance->y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player->instance->y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->instance->x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D) || mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->instance->x += 5;
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
	input_hook(data);
}

int32_t	main(void)
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	mlx_texture_t	*floor;
	uint32_t		xy[2];
	uint32_t		wh[2];
	t_data			data;

	xy[0] = 16 * 5 * 8;
	xy[1] = 16 * 15 * 5;
	wh[0] = 16 * 5;
	wh[1] = 16 * 5;
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	texture = mlx_load_png("dungeonTileset.png");
	data.image = mlx_texture_area_to_image(mlx, texture, xy, wh);
	int32_t i = mlx_image_to_window(mlx, data.image, 80, 80);
	// data.image->instances[i];
	data.player.instance = &data.image->instances[i];
	mlx_set_instance_depth(data.player.instance, 1);

	floor = mlx_load_png("dungeonTileset.png");
	data.background.image = mlx_texture_area_to_image(mlx, floor, (uint32_t[2]){0, 400}, (uint32_t[2]){320, 320});
	int32_t j = mlx_image_to_window(mlx, data.background.image, 0, 0);
	// mlx_image_to_window(mlx, data.background.image, 240, 320);
	data.background.instance = &data.background.image->instances[j];
	mlx_set_instance_depth(data.background.instance, 0);

	int32_t k = mlx_image_to_window(mlx, data.background.image, 0, 320);
	// mlx_image_to_window(mlx, data.background.image, 240, 320);
	data.background.instance = &data.background.image->instances[k];
	mlx_set_instance_depth(data.background.instance, 0);

	data.mlx = mlx;
	mlx_loop_hook(mlx, &hook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
