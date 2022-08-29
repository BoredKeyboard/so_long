/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 16:24:08 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/29 17:40:01 by mforstho      ########   odam.nl         */
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
	map_array = malloc((size_t)rows * sizeof(char *));
	y = 0;
	while (y < rows)
	{
		map_array[y] = map_lines->content;
		map_lines = map_lines->next;
		y++;
	}
	return (map_array);
}

// int	main(void)
// {
// 	char	**map_array;
// 	t_data	data;
// 	int		map;
// 	int		y;

// 	map = open("src/map/test_maps/testMap1.ber", O_RDONLY);
// 	save_map(map, &data);
// 	map_array = convert_map(&data);
// 	y = 0;
// 	while (y < ft_lstsize(data.map_lines))
// 	{
// 		printf("%s", map_array[y]);
// 		y++;
// 	}
// }
