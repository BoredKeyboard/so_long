/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_entities.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 15:12:56 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/25 17:40:13 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	draw_wall(mlx_t *mlx, t_data *data, size_t *pos)
{
	int	id;

	id = mlx_image_to_window(mlx, data->wall.image, pos[0] * 80, pos[1] * 80);
	mlx_set_instance_depth(&data->wall.image->instances[id], 1);
}

void	draw_floor(mlx_t *mlx, t_data *data, size_t *pos)
{
	int	id;

	id = mlx_image_to_window(mlx, data->floor.image, pos[0] * 80, pos[1] * 80);
	mlx_set_instance_depth(&data->floor.image->instances[id], 0);
}

void	draw_player(mlx_t *mlx, t_data *data, size_t *pos)
{
	int	id;

	id = mlx_image_to_window(mlx, data->player.image, pos[0] * 80, pos[1] * 80);
	data->player.instance = &data->player.image->instances[id];
	mlx_set_instance_depth(&data->player.image->instances[id], 2);
	id = mlx_image_to_window(mlx, data->floor.image, pos[0] * 80, pos[1] * 80);
	mlx_set_instance_depth(&data->floor.image->instances[id], 0);
}

void	draw_collectible(mlx_t *mlx, t_data *data, size_t *pos)
{
	int	id;

	id = mlx_image_to_window(mlx, data->collectible.image, pos[0] * 80, pos[1] * 80);
	mlx_set_instance_depth(&data->collectible.image->instances[id], 1);
	id = mlx_image_to_window(mlx, data->floor.image, pos[0] * 80, pos[1] * 80);
	mlx_set_instance_depth(&data->floor.image->instances[id], 0);
}

void	draw_exit(mlx_t *mlx, t_data *data, size_t *pos)
{
	int	id;

	id = mlx_image_to_window(mlx, data->exit.image, pos[0] * 80, pos[1] * 80);
	mlx_set_instance_depth(&data->exit.image->instances[id], 1);
	id = mlx_image_to_window(mlx, data->floor.image, pos[0] * 80, pos[1] * 80);
	mlx_set_instance_depth(&data->floor.image->instances[id], 0);
}
