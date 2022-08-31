/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 14:02:09 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 15:10:12 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <fcntl.h>

# include "libft/libft.h"
# include "src/get_next_line/get_next_line.h"

typedef struct s_player
{
	mlx_instance_t	*instance;
	mlx_image_t		*image;
	int				x;
	int				y;
	int				move_count;
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

typedef struct s_collectible_info
{
	int	x;
	int	y;
	int	id;
}	t_collectible_info;

typedef struct s_collectible
{
	mlx_image_t			*image;
	t_collectible_info	*info;
	int					count;
	int					total;
}	t_collectible;

typedef struct s_exit
{
	mlx_instance_t	*instance;
	mlx_image_t		*image;
	int				pos[2];
}	t_exit;

typedef struct s_data
{
	mlx_t			*mlx;
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
	ENTITY_ERROR,
	PATH_ERROR
}	t_error;

typedef enum e_status {
	OK = 0,
	ERROR,
}	t_status;

typedef void	(*t_draw_function)(mlx_t *mlx, t_data *data, size_t pos[2]);

# define VISITED '1'
# define VISITING '2'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define EMPTY '0'

// ENTITIES
// collectible_pickup.c
void		collectible_pickup(t_data *data);
// initialize_entity_data.c
void		initialize_entity_data(char **map_array, t_data *data);
// player_movement.c
void		move_player_up(t_player *player);
void		move_player_down(t_player *player);
void		move_player_left(t_player *player);
void		move_player_right(t_player *player);
void		real_input_hook(mlx_key_data_t keydata, void *param);

// MAP
// check_map_edge.c
t_status	check_map_edge(t_data *data);

// check_map_entities.c
t_status	check_map_entities(t_data *data);

// check_map_path.c
t_status	check_map_path(t_data *data);

// check_map_rect.c
t_status	check_map_rect(t_data *data);

// check_map.c
t_status	set_error(t_error error);
t_error		get_error(void);
void		print_err(void);
t_status	check_map(t_data *data);

// convert_map.c
char		**convert_map(t_data *data);

// draw_entities.c
void		draw_wall(mlx_t *mlx, t_data *data, size_t pos[2]);
void		draw_floor(mlx_t *mlx, t_data *data, size_t pos[2]);
void		draw_player(mlx_t *mlx, t_data *data, size_t pos[2]);
void		draw_collectible(mlx_t *mlx, t_data *data, size_t pos[2]);
void		draw_exit(mlx_t *mlx, t_data *data, size_t pos[2]);

// draw_map.c
void		initialize_textures(mlx_t *mlx, t_data *data);
void		init_textures_draw_map(mlx_t *mlx, t_data *data);
void		draw_entity(char c, mlx_t *mlx, t_data *data, size_t pos[2]);
void		draw_map(mlx_t *mlx, t_data *data);
int32_t		map_error(t_data *data);

// free_map_array.c
void		free_map_array(char **map_array);

// save_map.c
t_status	save_map(int map, t_data *data);

#endif
