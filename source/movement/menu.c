/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:18:24 by thitran         #+#    #+#             */
/*   Updated: 2025/06/10 19:41:48 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_menu(t_data *data)
{
	mlx_put_string(data->mlx, "ESC: Exit", 50, 35);
	mlx_put_string(data->mlx, "W/A/S/D: Move", 50, 55);
	mlx_put_string(data->mlx, "Left/right Arrow: Rotate", 50, 75);
}
