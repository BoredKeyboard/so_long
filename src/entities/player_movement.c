/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/30 13:30:12 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/31 18:33:22 by mforstho      ########   odam.nl         */
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
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& data->map_array[(player->y - 1)][player->x] != '1')
		move_player_up(player);
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& data->map_array[(player->y + 1)][player->x] != '1')
		move_player_down(player);
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& data->map_array[player->y][(player->x - 1)] != '1')
		move_player_left(player);
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& data->map_array[player->y][(player->x + 1)] != '1')
		move_player_right(player);
	ft_putnbr_fd(player->move_count, STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);
}
