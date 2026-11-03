/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:12:29 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 16:20:02 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->posx = 0;
	player->posy = 0;
	player->dirx = 0;
	player->diry = 0;
	player->planex = 0;
	player->planey = 0;
	player->rotate = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->has_moved = 0;
	player->has_player = false;
}

void	clear_player(t_player *player)
{
	if (!player)
		return ;
	player->posx = 0;
	player->posy = 0;
	player->dirx = 0;
	player->diry = 0;
	player->planex = 0;
	player->planey = 0;
	player->rotate = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->has_moved = 0;
	player->has_player = false;
}
