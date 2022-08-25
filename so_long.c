/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 15:54:14 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/25 17:39:32 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define X 8
#define Y 4

void	image_hook(mlx_t *mlx, mlx_image_t *image)	// Exit window
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, image);
}

void	input_hook(t_data *data)	// Player movement
{
	const t_player	*player = &data->player;
	mlx_t			*mlx;

	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
		player->instance->y -= 10;
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player->instance->y += 10;
	if (mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->instance->x -= 10;
	if (mlx_is_key_down(mlx, MLX_KEY_D) || mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->instance->x += 10;
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
	input_hook(data);
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
int	draw_map_test(mlx_t *mlx, t_data *data)
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

int32_t	main(void)
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	t_data			data;
	int				map;

	map = open("src/map//test_maps/testMap1.ber", O_RDONLY);
	save_map(map, &data);
	if (check_map(&data) != OK)
	{
		print_err();
		return (EXIT_FAILURE);
	}

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);

	texture = mlx_load_png("src/sprites/dungeonTileset.png");

	// Floor texture
	data.floor.image = mlx_texture_area_to_image(mlx, texture, (uint32_t[2]){160, 240}, (uint32_t[2]){80, 80});

	// Wall texture
	data.wall.image = mlx_texture_area_to_image(mlx, texture, (uint32_t[2]){0, 80}, (uint32_t[2]){80, 80});

	// Collectible texture
	data.collectible.image = mlx_texture_area_to_image(mlx, texture, (uint32_t[2]){80, 240}, (uint32_t[2]){80, 80});

	// Exit texture
	data.exit.image = mlx_texture_area_to_image(mlx, texture, (uint32_t[2]){320, 640}, (uint32_t[2]){80, 80});

	// Player texture
	data.player.image = mlx_texture_area_to_image(mlx, texture, (uint32_t[2]){80, 720}, (uint32_t[2]){80, 80});

	draw_map_test(mlx, &data);

	// int32_t i = mlx_image_to_window(mlx, data.player.image, 80, 80);
	// data.player.instance = &data.player.image->instances[i];
	// mlx_set_instance_depth(&data.player.image->instances[i], 2);

	data.mlx = mlx;
	mlx_loop_hook(mlx, &hook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
