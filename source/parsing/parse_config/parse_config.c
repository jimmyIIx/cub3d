/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:21:16 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 17:32:26 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool				process_pix_rgb(t_config *config,
							t_config_type type, char *line);
static t_config_type	get_config_type(char *line);

bool	parse_config(t_config *config, int fd)
{
	char			*line;
	int				config_count;
	t_config_type	type;

	config_count = 0;
	while (config_count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		type = get_config_type(line);
		if (type == NONE)
		{
			free(line);
			continue ;
		}
		else if (!process_pix_rgb(config, type, line))
			return (free(line), false);
		free(line);
		config_count++;
	}
	if (config_count == 6)
		return (true);
	return (ft_putstr_fd("Error:\nParsing: Invalid config number\n", 2), false);
}

static bool	process_pix_rgb(t_config *config, t_config_type type, char *line)
{
	if (type == NO || type == SO || type == WE || type == EA)
	{
		if (!stock_pix(config, type, line))
		{
			ft_putstr_fd("Error:\nParsing: Texture extraction error\n", 2);
			return (false);
		}
	}
	else if (type == F || type == C)
	{
		if (!stock_rgb(config, type, line))
		{
			ft_putstr_fd("Error:\nParsing: RGB extraction error\n", 2);
			return (false);
		}
	}
	return (true);
}

static t_config_type	get_config_type(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (NO);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (SO);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (WE);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (EA);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (F);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (C);
	else
		return (NONE);
}
