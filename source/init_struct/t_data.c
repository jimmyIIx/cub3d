/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:08:06 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 16:31:42 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	init_config(&data->config);
	init_map(&data->map);
	init_player(&data->player);
	init_ray(&data->ray);
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->line_length = 0;
	data->endian = 0;
}

void	clear_data(t_data *data)
{
	if (!data)
		return ;
	clear_config(&data->config);
	clear_map(&data->map);
	clear_player(&data->player);
	clear_ray(&data->ray);
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->line_length = 0;
	data->endian = 0;
}
