/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:41:56 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 16:46:07 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	stock_map(t_map *map, char *line, char *before_line, char *next_line)
{
	char	*tmp;
	char	*bef;
	char	*nxt;

	if (line != NULL && line[0] != '\n')
		map->maping = true;
	if (map->maping == false)
		return (true);
	tmp = ft_strtrim(line, "\n");
	bef = ft_strtrim(before_line, "\n");
	nxt = ft_strtrim(next_line, "\n");
	if (!check_map(map, tmp, bef, nxt))
	{
		ft_free(tmp);
		ft_free(bef);
		ft_free(nxt);
		return (false);
	}
	map->max_rows++;
	map->buffer = ft_strjoin_mod(map->buffer, tmp);
	map->buffer = ft_strjoin_mod(map->buffer, ";");
	ft_free(tmp);
	ft_free(bef);
	ft_free(nxt);
	return (true);
}
