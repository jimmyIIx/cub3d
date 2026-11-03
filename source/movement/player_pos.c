/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:18:24 by thitran           #+#    #+#             */
/*   Updated: 2025/06/27 17:26:14 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_pos_in_map(t_data *data, double x, double y);
static bool	is_valid_pos(t_data *data, double x, double y);

static bool	is_valid_pos_in_map(t_data *data, double x, double y)
{
	if (x < 0.25 || x >= (int)data->map.max_cols - 1.25)
		return (false);
	if (y < 0.25 || y >= (int)data->map.max_rows - 0.25)
		return (false);
	return (true);
}

static bool	is_valid_pos(t_data *data, double x, double y)
{
	if (is_valid_pos_in_map(data, x, y))
		return (true);
	return (false);
}

int	validate_move(t_data *data, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(data, new_x, data->player.posy))
	{
		data->player.posx = new_x;
		moved = 1;
	}
	if (is_valid_pos(data, data->player.posx, new_y))
	{
		data->player.posy = new_y;
		moved = 1;
	}
	return (moved);
}
