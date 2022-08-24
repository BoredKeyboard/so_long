/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_edge.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:13:41 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/24 15:46:00 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../so_long.h"

static int	horizontal_edge(char *map_line, size_t line_length)
{
	size_t	i;

	i = 0;
	while (i != (line_length - 1))
	{
		if (map_line[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

t_status	check_map_edge(t_data *data)
{
	size_t	line_length;
	char	*map_line;
	t_list	*map_lines;

	map_lines = data->map_lines;
	line_length = ft_strlen(map_lines->content);
	map_line = map_lines->content;
	if (horizontal_edge(map_line, line_length) == 1)
		return (set_error(EDGE_ERROR));
	map_lines = map_lines->next;
	while (map_lines->next != NULL)
	{
		map_line = map_lines->content;
		if (map_line[0] != '1' || map_line[line_length - 2] != '1')
			return (set_error(EDGE_ERROR));
		map_lines = map_lines->next;
	}
	map_line = map_lines->content;
	if (horizontal_edge(map_line, line_length) == 1)
		return (set_error(EDGE_ERROR));
	return (OK);
}
