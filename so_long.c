/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 15:54:14 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/30 18:04:38 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_hook(mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	initialize_entity_data(char **map_array, t_data *data)
{
	int		y;
	size_t	x;

	y = 0;
	while (map_array[y] != NULL)
	{
		x = 0;
		while (map_array[y][x] != '\0')
		{
			if (map_array[y][x] == 'P')
			{
				data->player.x = (int)x;
				data->player.y = y;
			}
			if (map_array[y][x] == 'C')
				data->collectible.total++;
			x++;
		}
		y++;
	}
}

void	real_input_hook(mlx_key_data_t keydata, void *param)	// Player movement
{
	t_data		*data;
	t_player	*player;
	mlx_t		*mlx;

	data = param;
	player = &data->player;
	mlx = data->mlx;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_W && data->map_array[(player->y - 1)][player->x] != '1')
		move_player_up(player);
	if (keydata.key == MLX_KEY_S && data->map_array[(player->y + 1)][player->x] != '1')
		move_player_down(player);
	if (keydata.key == MLX_KEY_A && data->map_array[player->y][(player->x - 1)] != '1')
		move_player_left(player);
	if (keydata.key == MLX_KEY_D && data->map_array[player->y][(player->x + 1)] != '1')
		move_player_right(player);
	ft_putendl_fd(ft_itoa(player->move_count), 1);
}

void	collectible_pickup(t_data *data)
{
	int				i;
	t_player		*player;
	t_collectible	*collectible;

	i = 0;
	player = &data->player;
	collectible = &data->collectible;
	if (data->map_array[player->y][player->x] == 'C')
	{
		collectible->count++;
		data->map_array[player->y][player->x] = '0';
		while (i < collectible->total)
		{
			if (collectible->info[i].x == player->x && collectible->info[i].y == player->y)
				collectible->image->instances[collectible->info[i].id].enabled = false;
			i++;
		}
	}
}

void	exit_game(mlx_t *mlx, t_data *data)
{
	t_player		*player;
	t_collectible	*collectible;

	player = &data->player;
	collectible = &data->collectible;
	if (collectible->count == collectible->total && data->map_array[player->y][player->x] == 'E')
		mlx_close_window(mlx);
}

void	hook(void *param)
{
	t_data		*data;
	mlx_t		*mlx;

	data = param;
	mlx = data->mlx;
	exit_hook(mlx);
	collectible_pickup(data);
	exit_game(mlx, data);
}

void	draw_entity(char c, mlx_t *mlx, t_data *data, size_t pos[2])
{
	static t_draw_function	draw_functions[] = {
	['1'] = draw_wall,
	['0'] = draw_floor,
	['P'] = draw_player,
	['C'] = draw_collectible,
	['E'] = draw_exit
	};

	return (draw_functions[(int)c](mlx, data, pos));
}

void	draw_map(mlx_t *mlx, t_data *data)
{
	size_t	pos[2];
	char	**map_array;

	map_array = data->map_array;
	pos[1] = 0;
	while (map_array[pos[1]] != NULL)
	{
		pos[0] = 0;
		while (map_array[pos[1]][pos[0]] != '\n')
		{
			draw_entity(map_array[pos[1]][pos[0]], mlx, data, pos);
			pos[0]++;
		}
		pos[1]++;
	}
}

void	initialize_textures(mlx_t *mlx, t_data *data)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("src/sprites/dungeonTileset.png");
	data->floor.image = mlx_texture_area_to_image(mlx, texture,
			(uint32_t[2]){160, 240}, (uint32_t[2]){80, 80});
	data->wall.image = mlx_texture_area_to_image(mlx, texture,
			(uint32_t[2]){0, 80}, (uint32_t[2]){80, 80});
	data->collectible.image = mlx_texture_area_to_image(mlx, texture,
			(uint32_t[2]){80, 240}, (uint32_t[2]){80, 80});
	data->exit.image = mlx_texture_area_to_image(mlx, texture,
			(uint32_t[2]){320, 640}, (uint32_t[2]){80, 80});
	data->player.image = mlx_texture_area_to_image(mlx, texture,
			(uint32_t[2]){80, 720}, (uint32_t[2]){80, 80});
}

int32_t	main(int argc, char *argv[])
{
	mlx_t			*mlx;
	t_data			data;
	int				map;

	ft_bzero(&data, sizeof(t_data));
	if (argc > 2 || argc < 2)
	{
		printf("Invalid amount of arguments\n");
		return (EXIT_FAILURE);
	}
	map = open(argv[1], O_RDONLY);
	save_map(map, &data);
	data.map_array = convert_map(&data);
	if (check_map(&data) != OK)
	{
		print_err();
		return (EXIT_FAILURE);
	}
	ft_lstclear(&data.map_lines, &free);
	initialize_entity_data(data.map_array, &data);
	data.collectible.info = malloc(sizeof(t_collectible_info) * data.collectible.total);

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);

	initialize_textures(mlx, &data);
	draw_map(mlx, &data);

	data.mlx = mlx;
	mlx_key_hook(mlx, &real_input_hook, &data);
	mlx_loop_hook(mlx, &hook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_map_array(data.map_array);
	free(data.collectible.info);
	return (EXIT_SUCCESS);
}
