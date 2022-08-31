/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 15:54:14 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 18:49:41 by mforstho      ########   odam.nl         */
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

t_status	validate_arguments(int argc, char *argv[])
{
	size_t	len;

	if (argc != 2)
		return (set_error(ARG_COUNT_ERROR));
	len = ft_strlen(argv[1]);
	if (len < 4)
		return (set_error(FILETYPE_ERROR));
	if (ft_strncmp(&argv[1][len - 4], ".ber", 4) != 0)
		return (set_error(FILETYPE_ERROR));
	return (OK);
}

int32_t	argument_error(void)
{
	ft_putendl_fd("Error", STDOUT_FILENO);
	ft_putendl_fd(
		"Invalid argument, only use one map that uses the '.ber' extension",
		STDOUT_FILENO);
	return (EXIT_FAILURE);
}

static t_status	run_mlx(t_data *data)
{
	mlx_key_hook(data->mlx, &real_input_hook, data);
	if (mlx_loop_hook(data->mlx, &hook, data) != true)
		return (set_error(MLX_ERROR));
	mlx_loop(data->mlx);
	return (OK);
}

void	free_data(t_data *data)
{
	if (data->mlx != NULL)
	{
		mlx_terminate(data->mlx);
		data->mlx = NULL;
	}
	free(data->collectible.info);
	data->collectible.info = NULL;
	ft_lstclear(&data->map_lines, &free);
	free_map_array(data->map_array);
	data->map_array = NULL;
}

t_status	validate_map(int map, t_data *data)
{
	if (save_map(map, data) != OK || convert_map(data) != OK
		|| check_map(data) != OK)
		return (ERROR);
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

int32_t	main(int argc, char *argv[])
{
	t_data			data;

	ft_bzero(&data, sizeof(t_data));
	if (validate_arguments(argc, argv) != OK
		|| validate_map(open(argv[1], O_RDONLY), &data) != OK
		|| load_entity_data(&data) != OK
		|| initialize_mlx_data(&data) != OK
		|| run_mlx(&data) != OK)
	{
		free_data(&data);
		ft_putendl_fd("Error", STDERR_FILENO);
		print_err();
		return (EXIT_FAILURE);
	}
	free_data(&data);
	return (EXIT_SUCCESS);
}
