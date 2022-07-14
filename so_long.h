/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 14:02:09 by mforstho      #+#    #+#                 */
/*   Updated: 2022/07/14 15:35:36 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>

// #include "libft/libft.h"
#include "src/get_next_line/get_next_line.h"

#ifndef SO_LONG_H
# define WIDTH 800
# define HEIGHT 800
# define MAP "src/map/testMap.ber"
#endif

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

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_player		player;
	t_background	background;
}	t_data;
