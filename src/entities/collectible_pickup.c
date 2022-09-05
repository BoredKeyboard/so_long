/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collectible_pickup.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 14:41:03 by mforstho      #+#    #+#                 */
/*   Updated: 2022/09/05 14:30:11 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			if (collectible->info[i].x == player->x
				&& collectible->info[i].y == player->y)
				collectible->image->instances[collectible->info[i].id].enabled
					= false;
			i++;
		}
	}
}
