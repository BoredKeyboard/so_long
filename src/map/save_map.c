/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 15:40:01 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/09 16:42:58 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

typedef enum e_error {
	NO_ERROR,
	MALLOC_ERROR,
	INT_ERROR,
	NON_RECT_ERROR
}	t_error;

typedef enum e_status {
	VALID = 0,
	ERROR,
}	t_status;

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
			return (ERROR); // set_error(MALLOC_ERROR);
		}
		printf("%s", ft_lstlast(data->map_lines)->content);
		temp_line = get_next_line(map);
	}
	return (VALID);
}

// typedef struct s_map
// {
// 	char			*line;
// 	struct s_map	*next;
// }	t_map;

// t_status	save_map(int map)
// {
// 	int		i;
// 	size_t	line_length;
// 	char	*temp_line;
// 	char	**saved_map;

// 	line_length = 1;
// 	i = 0;
// 	while (line_length != 0)
// 	{
// 		temp_line = get_next_line(map);
// 		saved_map[i] = temp_line;
// 		printf("%s", saved_map[i]);
// 		line_length = ft_strlen(temp_line);
// 		i++;
// 	}
// 	return (VALID);
// }

int	main(void)
{
	int		map;
	t_data	data;

	map = open("src/map/testMap.ber", O_RDONLY);
	save_map(map, &data);
	printf("%i\n", ft_lstsize(data.map_lines));
}
