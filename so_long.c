/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 15:54:14 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/29 18:15:23 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	image_hook(mlx_t *mlx, mlx_image_t *image)	// Exit window
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, image);
}

void	initialize_collision(char **map_array, t_data *data)
{
	int		y;
	size_t	x;

	y = 0;
	while (y < ft_lstsize(data->map_lines))
	{
		x = 0;
		while (x < ft_strlen(map_array[y]))
		{
			if (map_array[y][x] == 'P')
			{
				data->player.x = (int)x;
				data->player.y = y;
			}
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
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
	if (keydata.key == MLX_KEY_W && data->map_array[(player->y - 1)][player->x] != '1')
	{
		player->instance->y -= 80;
		player->y--;
	}
	if (keydata.key == MLX_KEY_S && data->map_array[(player->y + 1)][player->x] != '1')
	{
		player->instance->y += 80;
		player->y++;
	}
	if (keydata.key == MLX_KEY_A && data->map_array[player->y][(player->x - 1)] != '1')
	{
		player->instance->x -= 80;
		player->x--;
	}
	if (keydata.key == MLX_KEY_D && data->map_array[player->y][(player->x + 1)] != '1')
	{
		player->instance->x += 80;
		player->x++;
	}
}

void	hook(void *param)	// Central hook function
{
	t_data		*data;
	mlx_t		*mlx;
	mlx_image_t	*image;

	data = param;
	mlx = data->mlx;
	image = data->image;
	image_hook(mlx, image);
}

void	draw_entity(char c, mlx_t *mlx, t_data *data, size_t *pos)
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

// t_status van maken of int32_t
int	draw_map(mlx_t *mlx, t_data *data)
{
	t_list	*map_lines;
	size_t	pos[2];
	size_t	line_length;
	char	*map_line;

	pos[1] = 0;
	map_lines = data->map_lines;
	line_length = ft_strlen(map_lines->content);
	while (map_lines)
	{
		map_line = map_lines->content;
		pos[0] = 0;
		while (pos[0] != line_length - 1)
		{
			draw_entity(map_line[pos[0]], mlx, data, pos);
			pos[0]++;
		}
		map_lines = map_lines->next;
		pos[1]++;
	}
	return (0);
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

	if (argc > 2 || argc < 2)
	{
		printf("Invalid amount of arguments\n");
		return (EXIT_FAILURE);
	}
	map = open(argv[1], O_RDONLY);
	save_map(map, &data);
	if (check_map(&data) != OK)
	{
		print_err();
		return (EXIT_FAILURE);
	}
	data.map_array = convert_map(&data);
	initialize_collision(data.map_array, &data);

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
	return (EXIT_SUCCESS);
}
