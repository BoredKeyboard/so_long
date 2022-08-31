/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_rect.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:02:53 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 18:43:14 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../so_long.h"

t_status	check_map_rect(t_data *data)
{
	size_t	line_length;
	t_list	*map_lines;

	map_lines = data->map_lines;
	line_length = ft_strlen(map_lines->content);
	map_lines = map_lines->next;
	while (map_lines)
	{
		if (line_length != ft_strlen(map_lines->content))
			return (set_error(NON_RECT_ERROR));
		map_lines = map_lines->next;
	}
	return (OK);
}
