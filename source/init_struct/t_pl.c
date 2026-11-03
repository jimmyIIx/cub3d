/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:43 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/25 20:34:55 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_pl(t_pl *pl)
{
	pl->player = false;
	pl->player_x = 0;
	pl->player_y = 0;
}

void	clear_pl(t_pl *pl)
{
	pl->player = false;
	pl->player_x = 0;
	pl->player_y = 0;
}
