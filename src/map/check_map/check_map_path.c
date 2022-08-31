/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 15:47:48 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 15:13:53 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../so_long.h"

void	initialize_map_visit(t_data *data, char **map_array, int x, int y)
{
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
}

void	visit_nodes(char **map_array, int x, int y)
{
	if (map_array[y - 1][x] == EMPTY || map_array[y - 1][x]
		== COLLECTIBLE || map_array[y - 1][x] == EXIT)
		map_array[y - 1][x] = VISITING;
	if (map_array[y + 1][x] == EMPTY || map_array[y + 1][x]
		== COLLECTIBLE || map_array[y + 1][x] == EXIT)
		map_array[y + 1][x] = VISITING;
	if (map_array[y][x - 1] == EMPTY || map_array[y][x - 1]
		== COLLECTIBLE || map_array[y][x - 1] == EXIT)
		map_array[y][x - 1] = VISITING;
	if (map_array[y][x + 1] == EMPTY || map_array[y][x + 1]
		== COLLECTIBLE || map_array[y][x + 1] == EXIT)
		map_array[y][x + 1] = VISITING;
}

void	visit_array(char **map_array, int x, int y)
{
	bool	updated;

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
					visit_nodes(map_array, x, y);
					map_array[y][x] = VISITED;
					updated = true;
				}
				x++;
			}
			y++;
		}
	}
}

int	count_uncollected(char **map_array, int collectible_count, int x, int y)
{
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
	return (collectible_count);
}

t_status	check_map_path(t_data *data)
{
	char	**map_array;
	int		collectible_count;

	map_array = convert_map(data);
	initialize_map_visit(data, map_array, 0, 0);
	visit_array(map_array, 0, 0);
	collectible_count = count_uncollected(map_array, 0, 0, 0);
	if (collectible_count == 0
		&& map_array[data->exit.pos[1]][data->exit.pos[0]] == VISITED)
	{
		free_map_array(map_array);
		return (OK);
	}
	free_map_array(map_array);
	return (set_error(PATH_ERROR));
}
