/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:36:00 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 17:58:38 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	setup_line(char **line, char **before_line, char *next_line);
static void	clean(char *line, char *before_line, char *buffer);
static bool	stmap(t_map *map, char **line, char **before_line, char *next_line);
static bool	finalize_map(t_map *map, char *line, char *before_line);

bool	parse_map(t_map *map, int fd)
{
	map->buffer = ft_strdup("");
	if (!map->buffer)
		return (ft_putstr_fd("Error:\nMalloc\n", 2), false);
	while (1)
	{
		map->li.n_l = get_next_line(fd);
		if (!stmap(map, &map->li.ln, &map->li.b_l, map->li.n_l))
			return (clean(map->li.ln, map->li.b_l, map->buffer), false);
		if (map->li.ln == NULL || (map->li.ln != NULL && map->li.ln[0] == '\n'))
		{
			if (map->maping == false)
				continue ;
			if (map->maping == true)
			{
				map->complet = true;
				map->maping = false;
				if (map->li.n_l == NULL)
					break ;
			}
		}
		if (map->li.n_l == NULL || map->li.ln == NULL)
			break ;
	}
	return (finalize_map(map, map->li.ln, map->li.b_l));
}

static bool	stmap(t_map *map, char **line, char **before_l, char *next_l)
{
	if (map->complet == false && !stock_map(map, *line, *before_l, next_l))
		return (ft_free(next_l), false);
	if (*line == NULL)
	{
		*line = ft_strdup(next_l);
		ft_free(next_l);
		if (!*line)
			return (ft_putstr_fd("Error:\nMalloc\n", 2), false);
	}
	else if (!setup_line(line, before_l, next_l))
		return (false);
	else if (map->complet == true && ((*line != NULL && *line[0] != '\n')))
		return (ft_putstr_fd("Error:\nparsing: Invalid map\n", 2), false);
	return (true);
}

static bool	setup_line(char **line, char **before_line, char *next_line)
{
	char	*tmp;

	if (next_line == NULL)
	{
		ft_free(*line);
		*line = NULL;
		return (true);
	}
	tmp = *line;
	*line = ft_strdup(next_line);
	ft_free(next_line);
	if (!*line)
		return (ft_free(tmp), ft_putstr_fd("Error:\nMalloc\n", 2), false);
	ft_free(*before_line);
	*before_line = ft_strdup(tmp);
	if (!*before_line)
		return (ft_free(tmp), ft_putstr_fd("Error:\nMalloc\n", 2), false);
	ft_free(tmp);
	return (true);
}

static bool	finalize_map(t_map *map, char *line, char *before_line)
{
	ft_free(line);
	ft_free(before_line);
	map->map = ft_split(map->buffer, ';');
	if (!map->map)
	{
		ft_free(map->buffer);
		return (ft_putstr_fd("Error:\nMalloc\n", 2), false);
	}
	ft_free(map->buffer);
	if (map->pl.player == false)
		return (ft_putstr_fd("Error:\nParsing: No player\n", 2), false);
	return (true);
}

static void	clean(char *line, char *before_line, char *buffer)
{
	ft_free(line);
	ft_free(before_line);
	ft_free(buffer);
}
