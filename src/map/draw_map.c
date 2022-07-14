/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 14:51:13 by mforstho      #+#    #+#                 */
/*   Updated: 2022/07/14 15:11:43 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(mlx_t *mlx, t_data *data)
{
	int		map;
	char	*line;
	int		linelength;

	map = open("testMap.ber");
	line = malloc(sizeof(char) * linelength);
	get_next_line(map);
}
