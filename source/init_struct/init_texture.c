/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:02:19 by thitran           #+#    #+#             */
/*   Updated: 2025/06/27 16:50:58 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture(t_texture *tex, uint8_t *src_pixels);

void	init_textures(t_data *data)
{
	init_texture(&data->north, data->config.no_pix);
	init_texture(&data->south, data->config.so_pix);
	init_texture(&data->west, data->config.we_pix);
	init_texture(&data->east, data->config.ea_pix);
}

static void	init_texture(t_texture *tex, uint8_t *src_pixels)
{
	static uint8_t	dummy_pixel[4] = {255, 0, 255, 255};

	if (!src_pixels)
	{
		tex->pixels = dummy_pixel;
		tex->width = TEX_WIDTH;
		tex->height = TEX_HEIGHT;
	}
	else
	{
		tex->pixels = src_pixels;
		tex->width = TEX_WIDTH;
		tex->height = TEX_HEIGHT;
	}
}
