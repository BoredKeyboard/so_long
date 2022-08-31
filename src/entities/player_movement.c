/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/30 13:30:12 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 14:40:20 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	move_player_up(t_player *player)
{
	player->instance->y -= 80;
	player->y--;
	player->move_count++;
}

void	move_player_down(t_player *player)
{
	player->instance->y += 80;
	player->y++;
	player->move_count++;
}

void	move_player_left(t_player *player)
{
	player->instance->x -= 80;
	player->x--;
	player->move_count++;
}

void	move_player_right(t_player *player)
{
	player->instance->x += 80;
	player->x++;
	player->move_count++;
}

void	real_input_hook(mlx_key_data_t keydata, void *param)
{
	t_data		*data;
	t_player	*player;
	mlx_t		*mlx;

	data = param;
	player = &data->player;
	mlx = data->mlx;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_W
		&& data->map_array[(player->y - 1)][player->x] != '1')
		move_player_up(player);
	if (keydata.key == MLX_KEY_S
		&& data->map_array[(player->y + 1)][player->x] != '1')
		move_player_down(player);
	if (keydata.key == MLX_KEY_A
		&& data->map_array[player->y][(player->x - 1)] != '1')
		move_player_left(player);
	if (keydata.key == MLX_KEY_D
		&& data->map_array[player->y][(player->x + 1)] != '1')
		move_player_right(player);
	ft_putendl_fd(ft_itoa(player->move_count), 1);
}
