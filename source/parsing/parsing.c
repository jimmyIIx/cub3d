/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:18:24 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 17:23:06 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	parse(char *filename, t_data *data);
static void	last_ajust_player(t_data *data);
static bool	is_dir(char *arg);

bool	parsing(int argc, char **argv, t_data *data)
{
	if (!parse_args(argc, argv))
		return (false);
	init_data(data);
	if (!parse(argv[1], data))
		return (clear_data(data), false);
	last_ajust_player(data);
	return (true);
}

static bool	parse(char *filename, t_data *data)
{
	int	fd;

	if (is_dir(filename))
	{
		ft_putstr_fd("Error:\nParsing: The file is a folder\n", 2);
		return (false);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error:\nParsing: cannot open file\n", 2);
		return (false);
	}
	if (!parse_config(&data->config, fd))
		return (close(fd), false);
	if (!parse_map(&data->map, fd))
		return (close(fd), false);
	close(fd);
	return (true);
}

static void	last_ajust_player(t_data *data)
{
	data->player.posx = data->map.pl.player_x;
	data->player.posy = data->map.pl.player_y;
	if (data->map.pl.player_orientation == 'N')
	{
		data->player.diry = -1;
		data->player.planex = 0.66;
	}
	else if (data->map.pl.player_orientation == 'S')
	{
		data->player.diry = 1;
		data->player.planex = -0.66;
	}
	else if (data->map.pl.player_orientation == 'E')
	{
		data->player.dirx = 1;
		data->player.planey = 0.66;
	}
	else if (data->map.pl.player_orientation == 'W')
	{
		data->player.dirx = -1;
		data->player.planey = -0.66;
	}
}

static bool	is_dir(char *arg)
{
	int		fd;

	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (true);
	}
	return (false);
}
