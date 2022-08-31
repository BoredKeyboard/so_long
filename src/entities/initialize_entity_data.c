/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_entitie_data.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 14:39:56 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 14:40:06 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

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
