/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 15:54:14 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 15:25:11 by mforstho      ########   odam.nl         */
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

int32_t	argument_error(void)
{
	ft_putendl_fd(
		"Invalid argument, only use one map that uses the '.ber' extension", 1);
	return (EXIT_FAILURE);
}

static void	ft_mlx_init(mlx_t *mlx, t_data *data)
{
	mlx_key_hook(mlx, &real_input_hook, data);
	mlx_loop_hook(mlx, &hook, data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

int32_t	main(int argc, char *argv[])
{
	mlx_t			*mlx;
	t_data			data;

	if (argc > 2 || argc < 2
		|| !ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		return (argument_error());
	ft_bzero(&data, sizeof(t_data));
	save_map(open(argv[1], O_RDONLY), &data);
	data.map_array = convert_map(&data);
	if (check_map(&data) != OK)
		return (map_error(&data));
	initialize_entity_data(data.map_array, &data);
	data.collectible.info = malloc(sizeof(t_collectible_info)
			* data.collectible.total);
	mlx = mlx_init((ft_strlen(data.map_array[0]) - 1) * 80,
			ft_lstsize(data.map_lines) * 80, "MLX42", false);
	ft_lstclear(&data.map_lines, &free);
	if (!mlx)
		exit(EXIT_FAILURE);
	init_textures_draw_map(mlx, &data);
	data.mlx = mlx;
	ft_mlx_init(mlx, &data);
	free_map_array(data.map_array);
	free(data.collectible.info);
	return (EXIT_SUCCESS);
}
