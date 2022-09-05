/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_mlx_data.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/05 14:36:10 by mforstho      #+#    #+#                 */
/*   Updated: 2022/09/05 14:37:51 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_game(mlx_t *mlx, t_data *data)
{
	t_player		*player;
	t_collectible	*collectible;

	player = &data->player;
	collectible = &data->collectible;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (collectible->count == collectible->total
		&& data->map_array[player->y][player->x] == 'E')
		mlx_close_window(mlx);
}

void	hook(void *param)
{
	t_data		*data;
	mlx_t		*mlx;

	data = param;
	mlx = data->mlx;
	collectible_pickup(data);
	exit_game(mlx, data);
}

t_status	run_mlx(t_data *data)
{
	mlx_key_hook(data->mlx, &real_input_hook, data);
	if (mlx_loop_hook(data->mlx, &hook, data) != true)
		return (set_error(MLX_ERROR));
	mlx_loop(data->mlx);
	return (OK);
}

t_status	load_entity_data(t_data *data)
{
	initialize_entity_data(data->map_array, data);
	data->collectible.info = malloc(sizeof(t_collectible_info)
			* data->collectible.total);
	if (data->collectible.info == NULL)
		return (set_error(MALLOC_ERROR));
	return (OK);
}

t_status	initialize_mlx_data(t_data *data)
{
	data->mlx = mlx_init((ft_strlen(data->map_array[0]) - 1) * 80,
			ft_lstsize(data->map_lines) * 80, "MLX42", false);
	if (data->mlx == NULL)
		return (set_error(MLX_ERROR));
	if (init_textures_draw_map(data) != OK)
		return (ERROR);
	return (OK);
}
