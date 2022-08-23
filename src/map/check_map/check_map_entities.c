/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_entities.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:59:23 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/23 17:22:50 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../so_long.h"

t_status	check_map_entities(t_data *data)
{
	char	*map_line;
	size_t	line_length;
	size_t	i;
	int		entity_array[3];
	t_list	*map_lines;

	map_lines = data->map_lines;
	entity_array[0] = 0;
	entity_array[1] = 0;
	entity_array[2] = 0;
	line_length = ft_strlen(map_lines->content);
	i = 0;
	while (map_lines != NULL)
	{
		map_line = map_lines->content;
		i = 0;
		while (i != line_length - 1)
		{
			if (map_line[i] == 'E')
				entity_array[0]++;
			if (map_line[i] == 'C')
				entity_array[1]++;
			if (map_line[i] == 'P')
				entity_array[2]++;
			i++;
		}
		if (map_lines->next == NULL)
			break ;
		map_lines = map_lines->next;
	}
	if (entity_array[0] != 1 || entity_array[1] == 0 || entity_array[2] != 1)
		return (set_error(ENTITY_ERROR));
	return (OK);
}
