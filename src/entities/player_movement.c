/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/30 13:30:12 by mforstho      #+#    #+#                 */
/*   Updated: 2022/08/30 13:32:47 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	move_player_up(t_player *player)
{
	player->instance->y -= 80;
	player->y--;
}

void	move_player_down(t_player *player)
{
	player->instance->y += 80;
	player->y++;
}

void	move_player_left(t_player *player)
{
	player->instance->x -= 80;
	player->x--;
}

void	move_player_right(t_player *player)
{
	player->instance->x += 80;
	player->x++;
}
