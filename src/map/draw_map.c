/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 14:51:13 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 14:38:30 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	init_textures_draw_map(mlx_t *mlx, t_data *data)
{
	initialize_textures(mlx, data);
	draw_map(mlx, data);
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

int32_t	map_error(t_data *data)
{
	ft_putendl_fd("Error", 1);
	print_err();
	ft_lstclear(&data->map_lines, &free);
	free_map_array(data->map_array);
	return (EXIT_FAILURE);
}
