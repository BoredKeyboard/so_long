/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 14:51:13 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 18:24:24 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_status	initialize_textures(t_data *data)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("src/sprites/dungeonTileset.png");
	if (texture == NULL)
		return (set_error(MLX_ERROR));
	data->floor.image = mlx_texture_area_to_image(data->mlx, texture,
			(uint32_t[2]){160, 240}, (uint32_t[2]){80, 80});
	data->wall.image = mlx_texture_area_to_image(data->mlx, texture,
			(uint32_t[2]){0, 80}, (uint32_t[2]){80, 80});
	data->collectible.image = mlx_texture_area_to_image(data->mlx, texture,
			(uint32_t[2]){80, 240}, (uint32_t[2]){80, 80});
	data->exit.image = mlx_texture_area_to_image(data->mlx, texture,
			(uint32_t[2]){320, 640}, (uint32_t[2]){80, 80});
	data->player.image = mlx_texture_area_to_image(data->mlx, texture,
			(uint32_t[2]){80, 720}, (uint32_t[2]){80, 80});
	mlx_delete_texture(texture);
	return (OK);
}

t_status	init_textures_draw_map(t_data *data)
{
	if (initialize_textures(data) != OK)
		return (ERROR);
	if (draw_map(data) != OK)
		return (ERROR);
	return (OK);
}

t_status	draw_entity(char c, t_data *data, size_t pos[2])
{
	static t_draw_function	draw_functions[] = {
	['1'] = draw_wall,
	['0'] = draw_floor,
	['P'] = draw_player,
	['C'] = draw_collectible,
	['E'] = draw_exit
	};

	return (draw_functions[(int)c](data, pos));
}

t_status	draw_map(t_data *data)
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
			if (draw_entity(map_array[pos[1]][pos[0]], data, pos) != OK)
				return (ERROR);
			pos[0]++;
		}
		pos[1]++;
	}
	return (OK);
}
