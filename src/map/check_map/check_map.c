/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 14:52:07 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/23 17:11:44 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../so_long.h"

// #define VALID 1
// #define ERROR 0

// int	check_map(mlx_t *mlx, t_data *data)
// {
// 	int		map;
// 	int		ln_length;
// 	int		ln_length_next;
// 	char	*line;

// 	map = open("testMap.ber");

// 	printf("Setup:\n");
// 	ln_length = ft_strlen(get_next_line(map));
// 	printf("ln_length	  : %i\n", ln_length);
// 	ln_length_next = ft_strlen(get_next_line(map));
// 	printf("ln_length_next: %i\n", ln_length_next);
// 	printf("\nLoop:\n");
// 	while (ln_length_next != NULL)
// 	{
// 		if (ln_length != ln_length_next)
// 			return (ERROR);
// 		ln_length_next = ft_strlen(get_next_line(map));
// 		printf("ln_length_next: %i\n", ln_length_next);
// 	}
// 	return (VALID);
// }

static t_error	*get_error_ptr(void)
{
	static t_error	error = NO_ERROR;

	return (&error);
}

t_status	set_error(t_error error)
{
	*get_error_ptr() = error;
	if (error == NO_ERROR)
		return (OK);
	return (ERROR);
}

t_error	get_error(void)
{
	return (*get_error_ptr());
}

// t_status	check_map_entities(int map)
// {
//	Check of de map een 'C', 'P' en 'E' bevat
// }

// t_status	check_map_path(int map)
// {

// }

// int	main(void)
// {
// 	int	map;

// 	// if (check_map_test(map) != VALID)
// 	// 	return (get_error());

// 	map = open("src/map/testMap.ber", O_RDONLY);
// 	printf("Map: %i\n", map);
// 	// printf("result: %i\n", (int)check_map_test(map));
// 	if (check_map_test(map) == ERROR)
// 		print_err();
// 	return (1);
// }
