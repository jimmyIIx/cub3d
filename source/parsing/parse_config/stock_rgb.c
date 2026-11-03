/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:19:31 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 16:32:04 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	process_rgb_val(t_config *config, t_config_type type, char **tab);
static bool	is_valid_rgb(const char *line);
static bool	is_valid_trail(const char *line);
static bool	is_valid_num(const char *str);

bool	stock_rgb(t_config *config, t_config_type type, char *line)
{
	char	**tab;
	char	*trimmed;

	trimmed = ft_strtrim(line + 2, " \t\n\r");
	if (!trimmed || !is_valid_rgb(trimmed) || !is_valid_trail(trimmed))
		return (ft_free(trimmed), false);
	tab = ft_split(trimmed, ',');
	ft_free(trimmed);
	if (!tab)
		return (false);
	if (ft_tablen(tab) != 3)
		return (ft_free_deep(tab), false);
	if ((type == F && config->floor_set) || (type == C && config->ceiling_set))
		return (ft_free_deep(tab), false);
	if (!process_rgb_val(config, type, tab))
		return (ft_free_deep(tab), false);
	if (type == F)
		config->floor_set = true;
	else
		config->ceiling_set = true;
	ft_free_deep(tab);
	return (true);
}

static bool	process_rgb_val(t_config *config, t_config_type type, char **tab)
{
	int		i;
	int		val;
	char	*trimmed;

	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(tab[i], " \t");
		if (!trimmed)
			return (false);
		if (!is_valid_num(trimmed))
			return (ft_free(trimmed), false);
		val = ft_atoi(trimmed);
		ft_free(trimmed);
		if (val < 0 || val > 255)
			return (false);
		if (type == F)
			config->floor[i] = val;
		else if (type == C)
			config->ceiling[i] = val;
		i++;
	}
	return (true);
}

static bool	is_valid_rgb(const char *line)
{
	int		comma_count;
	int		i;
	char	c;

	comma_count = 0;
	i = 0;
	if (!line)
		return (false);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		c = line[i];
		if (c == ',')
		{
			comma_count++;
			if (comma_count > 2)
				return (false);
		}
		else if (!((c >= '0' && c <= '9') || c == ' ' || c == '\t'))
			return (false);
		i++;
	}
	return (comma_count == 2);
}

static bool	is_valid_trail(const char *line)
{
	int		count_commas;
	int		i;

	count_commas = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count_commas++;
		else if (count_commas == 2)
		{
			if (line[i] != ' ' && line[i] != '\t')
			{
				if (!(line[i] >= '0' && line[i] <= '9'))
					return (false);
			}
		}
		i++;
	}
	return (true);
}

static bool	is_valid_num(const char *str)
{
	size_t	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}
