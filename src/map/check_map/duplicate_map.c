/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   duplicate_map.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/05 14:25:51 by mforstho      #+#    #+#                 */
/*   Updated: 2022/09/05 14:26:02 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**duplicate_map(char **arr, int rows)
{
	int		y;
	char	**map_array;

	map_array = malloc(((size_t)rows + 1) * sizeof(char *));
	if (map_array == NULL)
		return (NULL);
	y = 0;
	while (arr[y] != NULL)
	{
		map_array[y] = strdup(arr[y]);
		if (map_array[y] == NULL)
		{
			free_map_array(map_array);
			return (NULL);
		}
		y++;
	}
	map_array[y] = NULL;
	return (map_array);
}
