/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 15:40:01 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 18:43:19 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

t_status	save_map(int map, t_data *data)
{
	int		map_size;
	char	*temp_line;

	map_size = 0;
	if (map < 0)
		return (set_error(OPEN_ERROR));
	data->map_lines = NULL;
	temp_line = get_next_line(map);
	while (temp_line != NULL)
	{
		if (ft_lstnew_back(&data->map_lines, temp_line) == NULL)
		{
			ft_lstclear(&data->map_lines, &free);
			free(temp_line);
			return (set_error(MALLOC_ERROR));
		}
		temp_line = get_next_line(map);
		map_size++;
	}
	if (map_size < 1)
		return (set_error(SMALL_MAP_ERROR));
	return (OK);
}
