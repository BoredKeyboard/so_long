/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 15:40:01 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/30 17:00:03 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

t_status	save_map(int map, t_data *data)
{
	char	*temp_line;

	data->map_lines = NULL;
	temp_line = get_next_line(map);
	while (temp_line != NULL)
	{
		if (ft_lstnew_back(&data->map_lines, temp_line) == NULL)
		{
			ft_lstclear(&data->map_lines, &free);
			return (set_error(MALLOC_ERROR));
		}
		temp_line = get_next_line(map);
	}
	return (OK);
}

void	print_err(void)
{
	static char	*error_texts[] = {
	[NO_ERROR] = "NO_ERROR",
	[MALLOC_ERROR] = "MALLOC_ERROR",
	[INT_ERROR] = "INT_ERROR",
	[NON_RECT_ERROR] = "NON_RECT_ERROR",
	[EDGE_ERROR] = "EDGE_ERROR",
	[ENTITY_ERROR] = "ENTITY_ERROR",
	[PATH_ERROR] = "PATH_ERROR",
	};

	ft_putendl_fd(error_texts[get_error()], 1);
}

t_status	check_map(t_data *data)
{
	if (check_map_rect(data) != OK || check_map_edge(data) != OK
		|| check_map_entities(data) != OK || check_map_path(data) != OK)
	{
		return (ERROR);
	}
	return (OK);
}

// int	main(void)
// {
// 	int		map;
// 	t_data	data;

// 	map = open("src/map/testMap.ber", O_RDONLY);
// 	save_map(map, &data);
// 	printf("Lines: %i\n\n", ft_lstsize(data.map_lines));
// 	if (check_map(&data) != OK)
// 	{
// 		print_err();
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }
