/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 14:52:07 by mforstho      #+#    #+#                 */
/*   Updated: 2022/07/14 15:59:20 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

#define VALID 1
#define ERROR 0

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

int	check_map_test(int map)
{
	size_t	ln_length;
	size_t	ln_length_next;
	char	*line;

	printf("Setup:\n");
	ln_length = ft_strlen((const char *)get_next_line(map));
	printf("ln_length	: %zu\n", ln_length);
	ln_length_next = ft_strlen(get_next_line(map));
	printf("ln_length_next	: %zu\n", ln_length_next);
	printf("\nLoop:\n");
	while (ln_length_next != 0)
	{
		if (ln_length != ln_length_next)
			return (ERROR);
		ln_length_next = ft_strlen(get_next_line(map));
		printf("ln_length_next: %zu\n", ln_length_next);
	}
	return (VALID);
}

int	main(void)
{
	int	map;

	map = open("src/map/testMap.ber", O_RDONLY);
	printf("Map: %i\n", map);
	printf("result: %i", check_map_test(map));
	return (1);
}
