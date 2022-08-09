/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 14:52:07 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/09 15:46:50 by mforstho      ########   odam.nl         */
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
		return (VALID);
	return (ERROR);
}

t_error	get_error(void)
{
	return (*get_error_ptr());
}

// t_status	check_map_test(int map)
// {
// 	size_t	ln_length;
// 	size_t	ln_length_next;
// 	char	*line;

// 	printf("Setup:\n");
// 	ln_length = ft_strlen((const char *)get_next_line(map));
// 	printf("ln_length	: %zu\n", ln_length);
// 	ln_length_next = ft_strlen(get_next_line(map));
// 	printf("ln_length_next	: %zu\n", ln_length_next);
// 	printf("\nLoop:\n");
// 	while (ln_length_next != 0)
// 	{
// 		if (ln_length != ln_length_next)
// 			return (set_error(MALLOC_ERROR));
// 		ln_length_next = ft_strlen(get_next_line(map));
// 		printf("ln_length_next: %zu\n", ln_length_next);
// 	}
// 	return (VALID);
// }

// t_status	save_map(int map)
// {
// 	int		i;
// 	size_t	line_length;
// 	char	*temp_line;
// 	char	**saved_map;

// 	i = 0;
// 	while (line_length != 0)
// 	{
// 		temp_line = get_next_line(map);
// 		saved_map[i] = temp_line;
// 		line_length = ft_strlen(temp_line);
// 		i++;
// 	}
// }

t_status	check_map_rect(int map)
{
	size_t	ln_length;
	size_t	ln_length_next;
	char	*row;

	printf("Setup:\n");
	ln_length = -1;
	printf("ln_length	: %zu\n", ln_length);
	row = get_next_line(map);
	ln_length_next = ft_strlen(row);
	if (row[ln_length_next - 1] == '\n')
		ln_length_next -= 1;
	printf("ln_length_next	: %zu\n", ln_length_next);
	printf("\nLoop:\n");
	while (ln_length_next != 0)
	{
		if ((int)ln_length != -1 && ln_length != ln_length_next)
			return (set_error(NON_RECT_ERROR));
		ln_length = ln_length_next;
		row = get_next_line(map);
		if (row == NULL)
			break ;
		ln_length_next = ft_strlen(row);
		if (row[ln_length_next - 1] == '\n')
			ln_length_next -= 1;
		printf("ln_length_next: %zu\n", ln_length_next);
	}
	return (VALID);
}

// t_status	check_map_edge(int map)
// {
//	In de eerste regel checken of alle karakters een 1 zijn
//	Van de tweede tot een na laatste regel checken of de karakters een 1 zijn
//	In de laatste regel kijken of alle karakters een 1 zijn
// }

// t_status	check_map_entities(int map)
// {
//	Check of de map een 'C', 'P' en 'E' bevat
// }

// t_status	check_map_path(int map)
// {

// }

void	print_err(void)
{
	const static char	*jump_table[] = {
	[NON_RECT_ERROR] = "NON_RECT_ERROR",
	[NO_ERROR] = "NO_ERROR",
	[MALLOC_ERROR] = "MALLOC_ERROR",
	[INT_ERROR] = "INT_ERROR",

	};

	ft_putendl_fd((char *)jump_table[get_error()], 1);
}

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


/*

char *row = get_next_line(map);

ln_length = ft_strlen(row);

if (row[ln_length_next - 1] == '\n')
	ln_length_next -= 1;


linked list om rows in op te slaan

*/
