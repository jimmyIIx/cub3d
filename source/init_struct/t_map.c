/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:11:23 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 16:31:29 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map)
{
	map->map = NULL;
	map->max_rows = 0;
	map->max_cols = 0;
	map->buffer = NULL;
	map->maping = false;
	map->complet = false;
	init_li(&map->li);
	init_pl(&map->pl);
}

void	clear_map(t_map *map)
{
	if (!map)
		return ;
	ft_free_deep(map->map);
	map->max_rows = 0;
	map->max_cols = 0;
	map->maping = false;
	map->complet = false;
	clear_pl(&map->pl);
}
