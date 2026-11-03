/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:11:09 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 16:51:40 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	init_game(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3d", true);
	if (!data->mlx)
	{
		ft_putstr_fd("error: Failed to init MLX42\n", 2);
		clear_data(data);
		return (false);
	}
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
	{
		printf("error:\nFailed to create image\n");
		mlx_terminate(data->mlx);
		clear_data(data);
		return (false);
	}
	return (true);
}
