/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:38:28 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/29 12:30:40 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	listen_for_input(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parsing(argc, argv, &data))
		return (EXIT_FAILURE);
	if (!init_game(&data))
		return (ft_putstr_fd("error:\nImit MLX\n", 2), EXIT_FAILURE);
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0)
	{
		ft_putstr_fd("error:\nFailed to put image to window\n", 2);
		mlx_terminate(data.mlx);
		clear_data(&data);
		return (EXIT_FAILURE);
	}
	init_textures(&data);
	print_menu(&data);
	listen_for_input(&data);
	mlx_loop_hook(data.mlx, update_and_render, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	clear_data(&data);
	return (EXIT_SUCCESS);
}

void	on_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_delete_image(data->mlx, data->img);
	mlx_close_window(data->mlx);
}

static void	listen_for_input(t_data *data)
{
	mlx_close_hook(data->mlx, on_close, data);
}
