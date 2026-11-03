/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:38:28 by thitran           #+#    #+#             */
/*   Updated: 2025/06/20 03:16:06 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			handle_key_inputs(t_data *data);
static uint32_t		rgb_to_int(int rgb[3]);
static int			clamp_rgb(int value);
static void			draw_ceiling_and_floor(t_data *data);

void	update_and_render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		on_close(data);
		return ;
	}
	handle_key_inputs(data);
	move_player(data);
	draw_ceiling_and_floor(data);
	raycasting_loop(data);
}

static void	handle_key_inputs(t_data *data)
{
	data->player.move_x = 0;
	data->player.move_y = 0;
	data->player.rotate = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player.move_y = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player.move_y = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->player.move_x = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player.move_x = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.rotate = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.rotate = 1;
}

static int	clamp_rgb(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

static uint32_t	rgb_to_int(int rgb[3])
{
	int	r;
	int	g;
	int	b;

	r = clamp_rgb(rgb[0]);
	g = clamp_rgb(rgb[1]);
	b = clamp_rgb(rgb[2]);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

static void	draw_ceiling_and_floor(t_data *data)
{
	int			x;
	int			y;
	uint32_t	ceiling_color;
	uint32_t	floor_color;

	ceiling_color = rgb_to_int(data->config.ceiling);
	floor_color = rgb_to_int(data->config.floor);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				mlx_put_pixel(data->img, x, y, ceiling_color);
			else
				mlx_put_pixel(data->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}
