/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:34:03 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/28 14:49:39 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ply(t_map *map, char *line, char c, size_t x);
static void	count_cols(t_map *map, size_t index);

bool	check_map(t_map *map, char *line, char *before_line, char *next_line)
{
	char	c;
	size_t	i;

	i = 0;
	while (line[i])
	{
		c = line[i];
		if (!ft_strchr("01 NSEW", c))
			return (ft_putstr_fd("Error:\nParsing: Invalid char\n", 2), false);
		if (!ply(map, line, c, i))
			return (false);
		if (c == '0'
			&& (((i > 0 && line[i - 1] == ' ') || (i == 0))
				|| ((i + 1 < ft_strlen(line) && line[i + 1] == ' ')
					|| (i + 1 == ft_strlen(line)))
				|| ((i + 1 < ft_strlen(before_line) && before_line[i] == ' ')
					|| (i + 1 > ft_strlen(before_line)))
				|| ((i + 1 < ft_strlen(next_line) && next_line[i] == ' ')
					|| (i + 1 > ft_strlen(next_line)))))
			return (ft_putstr_fd("Error:\nParsing: Invalid map\n", 2), false);
		i++;
	}
	count_cols(map, i);
	return (true);
}

static bool	ply(t_map *map, char *line, char c, size_t x)
{
	if (!ft_strchr("NSEW", c))
		return (true);
	if (map->pl.player == true)
		return (ft_putstr_fd("Error:\nParsing: Too many players\n", 2), false);
	map->pl.player_x = (double) x + 0.5;
	map->pl.player_y = (double) map->max_rows + 0.5;
	map->pl.player_orientation = c;
	map->pl.player = true;
	line[x] = '0';
	return (true);
}

static void	count_cols(t_map *map, size_t index)
{
	if (index > map->max_cols)
		map->max_cols = index;
}
