/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_config.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:09:03 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 16:19:57 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_config *config)
{
	config->no_pix = NULL;
	config->so_pix = NULL;
	config->we_pix = NULL;
	config->ea_pix = NULL;
	config->floor[0] = 0;
	config->floor[1] = 0;
	config->floor[2] = 0;
	config->ceiling[0] = 0;
	config->ceiling[1] = 0;
	config->ceiling[2] = 0;
	config->no_set = false;
	config->so_set = false;
	config->we_set = false;
	config->ea_set = false;
	config->floor_set = false;
	config->ceiling_set = false;
}

void	clear_config(t_config *config)
{
	int	i;

	i = 0;
	if (!config)
		return ;
	while (i < 3)
	{
		config->floor[i] = -1;
		config->ceiling[i] = -1;
		i++;
	}
	free(config->no_pix);
	free(config->so_pix);
	free(config->we_pix);
	free(config->ea_pix);
	config->no_pix = NULL;
	config->so_pix = NULL;
	config->we_pix = NULL;
	config->ea_pix = NULL;
	config->no_set = false;
	config->so_set = false;
	config->we_set = false;
	config->ea_set = false;
	config->floor_set = false;
	config->ceiling_set = false;
}
