/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 14:02:09 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/29 18:00:22 by mforstho      ########   odam.nl         */
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
	mlx_image_t		*image;
	int				x;
	int				y;
}	t_player;

typedef struct s_floor
{
	mlx_instance_t	*instance;
	mlx_image_t		*image;
}	t_floor;

typedef struct s_wall
{
	mlx_instance_t	*instance;
	mlx_image_t		*image;
}	t_wall;

typedef struct s_collectible
{
	mlx_instance_t	*instance;
	mlx_image_t		*image;
}	t_collectible;

typedef struct	s_exit
{
	mlx_instance_t	*instance;
	mlx_image_t		*image;
}	t_exit;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_player		player;
	t_floor			floor;
	t_wall			wall;
	t_collectible	collectible;
	t_exit			exit;
	t_list			*map_lines;
	char			**map_array;
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

typedef void	(*t_draw_function)(mlx_t *mlx, t_data *data, size_t *pos);

#ifndef SO_LONG_H
# define WIDTH 1600
# define HEIGHT 1600
# define MAP "src/map/testMap.ber"

// static t_error	*get_error_ptr(void);
t_status	set_error(t_error error);
t_error		get_error(void);

t_status	save_map(int map, t_data *data);
void		print_err(void);
t_status	check_map(t_data *data);

void		draw_wall(mlx_t *mlx, t_data *data, size_t *pos);
void		draw_floor(mlx_t *mlx, t_data *data, size_t *pos);
void		draw_player(mlx_t *mlx, t_data *data, size_t *pos);
void		draw_collectible(mlx_t *mlx, t_data *data, size_t *pos);
void		draw_exit(mlx_t *mlx, t_data *data, size_t *pos);

t_status	check_map_edge(t_data *data);
t_status	check_map_entities(t_data *data);
t_status	check_map_rect(t_data *data);

char		**convert_map(t_data *data);
#endif
