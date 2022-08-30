/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 15:47:48 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/30 18:11:15 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../so_long.h"

void	free_map_array(char **map_array)
{
	int	y;

	y = 0;
	while (map_array[y] != NULL)
	{
		free(map_array[y]);
		y++;
	}
	free(map_array);
}

t_status	check_map_path(t_data *data)
{
	char	**map_array;
	int		x;
	int		y;
	int		collectible_count;
	bool	updated;

	map_array = convert_map(data);
	collectible_count = 0;
	y = 0;
	while (map_array[y] != NULL)
	{
		x = 0;
		while (map_array[y][x] != '\0')
		{
			if (map_array[y][x] == PLAYER)
				map_array[y][x] = VISITING;
			if (map_array[y][x] == EXIT)
			{
				data->exit.pos[0] = x;
				data->exit.pos[1] = y;
			}
			x++;
		}
		y++;
	}


	updated = true;
	while (updated)
	{
		updated = false;
		y = 0;
		while (map_array[y] != NULL)
		{
			x = 0;
			while (map_array[y][x] != '\0')
			{
				if (map_array[y][x] == VISITING)
				{
					if (map_array[y - 1][x] == EMPTY || map_array[y - 1][x] == COLLECTIBLE || map_array[y - 1][x] == EXIT)
						map_array[y - 1][x] = VISITING;
					if (map_array[y + 1][x] == EMPTY || map_array[y + 1][x] == COLLECTIBLE || map_array[y + 1][x] == EXIT)
						map_array[y + 1][x] = VISITING;
					if (map_array[y][x - 1] == EMPTY || map_array[y][x - 1] == COLLECTIBLE || map_array[y][x - 1] == EXIT)
						map_array[y][x - 1] = VISITING;
					if (map_array[y][x + 1] == EMPTY || map_array[y][x + 1] == COLLECTIBLE || map_array[y][x + 1] == EXIT)
						map_array[y][x + 1] = VISITING;
					map_array[y][x] = VISITED;
					updated = true;
				}
				x++;
			}
			y++;
		}
	}

	y = 0;
	while (map_array[y] != NULL)
	{
		x = 0;
		while (map_array[y][x] != '\0')
		{
			if (map_array[y][x] == COLLECTIBLE)
				collectible_count++;
			x++;
		}
		y++;
	}

	if (collectible_count == 0 && map_array[data->exit.pos[1]][data->exit.pos[0]] == VISITED)
	{
		free_map_array(map_array);
		return (OK);
	}
	free_map_array(map_array);
	return (set_error(PATH_ERROR));
}
