/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 14:52:07 by mforstho      #+#    #+#                 */
/*   Updated: 2022/09/05 14:30:55 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	[OPEN_ERROR] = "OPEN_ERROR",
	[SMALL_MAP_ERROR] = "SMALL_MAP_ERROR",
	[MLX_ERROR] = "MLX_ERROR",
	[ARG_COUNT_ERROR] = "ARG_COUNT_ERROR",
	[FILETYPE_ERROR] = "FILETYPE_ERROR",
	[INVALID_CHAR_ERROR] = "INVALID_CHAR_ERROR",
	};

	ft_putendl_fd(error_texts[get_error()], STDERR_FILENO);
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
