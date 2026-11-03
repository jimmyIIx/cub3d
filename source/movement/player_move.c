/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:18:24 by thitran           #+#    #+#             */
/*   Updated: 2025/06/10 19:41:48 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	move_player_forward(t_data *data);
static int	move_player_backward(t_data *data);
static int	move_player_left(t_data *data);
static int	move_player_right(t_data *data);

static int	move_player_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.posx + data->player.dirx * MOVESPEED;
	new_y = data->player.posy + data->player.diry * MOVESPEED;
	if (validate_move(data, new_x, new_y))
	{
		data->player.posx = new_x;
		data->player.posy = new_y;
		return (1);
	}
	return (0);
}

static int	move_player_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.posx - data->player.dirx * MOVESPEED;
	new_y = data->player.posy - data->player.diry * MOVESPEED;
	if (validate_move(data, new_x, new_y))
	{
		data->player.posx = new_x;
		data->player.posy = new_y;
		return (1);
	}
	return (0);
}

static int	move_player_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.posx + data->player.diry * MOVESPEED;
	new_y = data->player.posy - data->player.dirx * MOVESPEED;
	if (validate_move(data, new_x, new_y))
	{
		data->player.posx = new_x;
		data->player.posy = new_y;
		return (1);
	}
	return (0);
}

static int	move_player_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.posx - data->player.diry * MOVESPEED;
	new_y = data->player.posy + data->player.dirx * MOVESPEED;
	if (validate_move(data, new_x, new_y))
	{
		data->player.posx = new_x;
		data->player.posy = new_y;
		return (1);
	}
	return (0);
}

int	move_player(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->player.move_y == 1)
		moved += move_player_forward(data);
	if (data->player.move_y == -1)
		moved += move_player_backward(data);
	if (data->player.move_x == -1)
		moved += move_player_left(data);
	if (data->player.move_x == 1)
		moved += move_player_right(data);
	if (data->player.rotate != 0)
		moved += rotate_player(data, data->player.rotate);
	return (moved);
}
