/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 16:24:08 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 14:30:58 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

char	**convert_map(t_data *data)
{
	int		rows;
	int		y;
	char	**map_array;
	t_list	*map_lines;

	map_lines = data->map_lines;
	rows = ft_lstsize(map_lines);
	map_array = malloc(((size_t)rows + 1) * sizeof(char *));
	y = 0;
	while (y < rows)
	{
		map_array[y] = strdup(map_lines->content);
		map_lines = map_lines->next;
		y++;
	}
	map_array[y] = NULL;
	return (map_array);
}
