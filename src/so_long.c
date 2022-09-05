/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 15:54:14 by mforstho      #+#    #+#                 */
/*   Updated: 2022/09/05 14:38:06 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_status	validate_arguments(int argc, char *argv[])
{
	size_t	len;

	if (argc != 2)
		return (set_error(ARG_COUNT_ERROR));
	len = ft_strlen(argv[1]);
	if (len < 4)
		return (set_error(FILETYPE_ERROR));
	if (ft_strncmp(&argv[1][len - 4], ".ber", 4) != 0)
		return (set_error(FILETYPE_ERROR));
	return (OK);
}

void	free_data(t_data *data)
{
	if (data->mlx != NULL)
	{
		mlx_terminate(data->mlx);
		data->mlx = NULL;
	}
	free(data->collectible.info);
	data->collectible.info = NULL;
	ft_lstclear(&data->map_lines, &free);
	free_map_array(data->map_array);
	data->map_array = NULL;
}

t_status	validate_map(int map, t_data *data)
{
	if (save_map(map, data) != OK || convert_map(data) != OK
		|| check_map(data) != OK)
		return (ERROR);
	return (OK);
}

int32_t	main(int argc, char *argv[])
{
	t_data			data;

	ft_bzero(&data, sizeof(t_data));
	if (validate_arguments(argc, argv) != OK
		|| validate_map(open(argv[1], O_RDONLY), &data) != OK
		|| load_entity_data(&data) != OK
		|| initialize_mlx_data(&data) != OK
		|| run_mlx(&data) != OK)
	{
		free_data(&data);
		ft_putendl_fd("Error", STDERR_FILENO);
		print_err();
		return (EXIT_FAILURE);
	}
	free_data(&data);
	return (EXIT_SUCCESS);
}
