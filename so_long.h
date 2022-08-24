/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 14:02:09 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/24 17:04:27 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>

#include "libft/libft.h"
#include "src/get_next_line/get_next_line.h"

typedef struct s_player
{
	mlx_instance_t	*instance;
	int				health;
}	t_player;

typedef struct s_background
{
	mlx_instance_t	*instance;
	mlx_image_t		*image;
}	t_background;

typedef struct s_wall
{
	mlx_instance_t	*instance;
	mlx_image_t		*image;
}	t_wall;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_player		player;
	t_background	background;
	t_wall			wall;
	t_list			*map_lines;
}	t_data;

typedef enum e_error {
	NO_ERROR,
	MALLOC_ERROR,
	INT_ERROR,
	NON_RECT_ERROR,
	EDGE_ERROR,
	ENTITY_ERROR
}	t_error;

typedef enum e_status {
	OK = 0,
	ERROR,
}	t_status;

#ifndef SO_LONG_H
# define WIDTH 800
# define HEIGHT 800
# define MAP "src/map/testMap.ber"

// static t_error	*get_error_ptr(void);
t_status		set_error(t_error error);
t_error			get_error(void);
void			print_err(void);
t_status		check_map_edge(t_data *data);
t_status		check_map_entities(t_data *data);
t_status		check_map_rect(t_data *data);
#endif

