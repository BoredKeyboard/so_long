/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_map_array.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:09:14 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 15:09:41 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
