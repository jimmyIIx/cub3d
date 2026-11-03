/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:18:24 by thitran           #+#    #+#             */
/*   Updated: 2025/06/10 19:41:48 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_ray(t_ray *ray, int x, int screenWidth, t_player *player);
static void	calc_step_side(t_ray *ray, t_player *player);
static void	perform_dda(t_ray *ray, char **map);
static void	calc_wall(t_ray *ray, t_player *player, int screenHeight);

static void	setup_ray(t_ray *ray, int x, int screenWidth, t_player *player)
{
	ray->camerax = 2 * x / (double)screenWidth - 1;
	ray->raydirx = player->dirx + player->planex * ray->camerax;
	ray->raydiry = player->diry + player->planey * ray->camerax;
	ray->mapx = (int)player->posx;
	ray->mapy = (int)player->posy;
	ray->deltadistx = fabs(1 / ray->raydirx);
	ray->deltadisty = fabs(1 / ray->raydiry);
	ray->hit = 0;
}

static void	calc_step_side(t_ray *ray, t_player *player)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (player->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - player->posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (player->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - player->posy) * ray->deltadisty;
	}
}

static void	perform_dda(t_ray *ray, char **map)
{
	while (!ray->hit)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (ray->mapx < 0 || ray->mapy < 0
			|| !map[ray->mapy] || ray->mapx >= (int)ft_strlen(map[ray->mapy]))
		{
			ray->hit = 1;
			return ;
		}
		if (map[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
}

static void	calc_wall(t_ray *ray, t_player *player, int screenHeight)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->mapx - player->posx
				+ (1 - ray->stepx) / 2) / ray->raydirx;
	else
		ray->perpwalldist = (ray->mapy - player->posy
				+ (1 - ray->stepy) / 2) / ray->raydiry;
	ray->lineheight = (int)(screenHeight / ray->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + screenHeight / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + screenHeight / 2;
	if (ray->drawend >= screenHeight)
		ray->drawend = screenHeight - 1;
}

void	raycasting_loop(t_data *data)
{
	int		x;
	t_ray	*ray;

	if (!data->map.map || !data->map.map[0])
	{
		ft_putendl_fd("Error: Invalid map data", 2);
		exit(EXIT_FAILURE);
	}
	data->win_width = WIN_WIDTH;
	data->win_height = WIN_HEIGHT;
	ray = &data->ray;
	x = 0;
	while (x < data->win_width)
	{
		setup_ray(ray, x, data->win_width, &data->player);
		calc_step_side(ray, &data->player);
		perform_dda(ray, data->map.map);
		calc_wall(ray, &data->player, data->win_height);
		draw_textured_column(data, x, ray);
		x++;
	}
}
