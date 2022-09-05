/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_entities.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 15:12:56 by mforstho      #+#    #+#                 */
/*   Updated: 2022/09/05 14:31:10 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_status	draw_wall(t_data *data, size_t pos[2])
{
	int	id;

	id = mlx_image_to_window(data->mlx, data->wall.image, pos[0] * 80,
			pos[1] * 80);
	if (id < 0)
		return (set_error(MLX_ERROR));
	mlx_set_instance_depth(&data->wall.image->instances[id], 1);
	return (OK);
}

t_status	draw_floor(t_data *data, size_t pos[2])
{
	int	id;

	id = mlx_image_to_window(data->mlx, data->floor.image, pos[0] * 80,
			pos[1] * 80);
	if (id < 0)
		return (set_error(MLX_ERROR));
	mlx_set_instance_depth(&data->floor.image->instances[id], 0);
	return (OK);
}

t_status	draw_player(t_data *data, size_t pos[2])
{
	int	id;

	id = mlx_image_to_window(data->mlx, data->player.image, pos[0] * 80,
			pos[1] * 80);
	if (id < 0)
		return (set_error(MLX_ERROR));
	data->player.instance = &data->player.image->instances[id];
	mlx_set_instance_depth(&data->player.image->instances[id], 2);
	id = mlx_image_to_window(data->mlx, data->floor.image, pos[0] * 80,
			pos[1] * 80);
	if (id < 0)
		return (set_error(MLX_ERROR));
	mlx_set_instance_depth(&data->floor.image->instances[id], 0);
	return (OK);
}

t_status	draw_collectible(t_data *data, size_t pos[2])
{
	int			id;
	static int	id_index;

	id = mlx_image_to_window(data->mlx, data->collectible.image, pos[0] * 80,
			pos[1] * 80);
	if (id < 0)
		return (set_error(MLX_ERROR));
	mlx_set_instance_depth(&data->collectible.image->instances[id], 1);
	data->collectible.info[id_index].id = id;
	data->collectible.info[id_index].x = pos[0];
	data->collectible.info[id_index].y = pos[1];
	id_index++;
	id = mlx_image_to_window(data->mlx, data->floor.image, pos[0] * 80,
			pos[1] * 80);
	if (id < 0)
		return (set_error(MLX_ERROR));
	mlx_set_instance_depth(&data->floor.image->instances[id], 0);
	return (OK);
}

t_status	draw_exit(t_data *data, size_t pos[2])
{
	int	id;

	id = mlx_image_to_window(data->mlx, data->exit.image, pos[0] * 80,
			pos[1] * 80);
	if (id < 0)
		return (set_error(MLX_ERROR));
	mlx_set_instance_depth(&data->exit.image->instances[id], 1);
	id = mlx_image_to_window(data->mlx, data->floor.image, pos[0] * 80,
			pos[1] * 80);
	if (id < 0)
		return (set_error(MLX_ERROR));
	mlx_set_instance_depth(&data->floor.image->instances[id], 0);
	return (OK);
}
