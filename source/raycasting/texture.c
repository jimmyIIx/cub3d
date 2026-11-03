/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                               		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:32:24 by thitran          #+#    #+#              */
/*   Updated: 2025/06/16 19:33:13 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*get_texture(t_data *data, t_ray *ray);
static int			get_texture_x(t_data *data, t_ray *ray, t_texture *tex);
static void			draw_column_pixels(t_tex_draw_params *p);

static t_texture	*get_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->raydirx > 0)
			return (&data->west);
		else
			return (&data->east);
	}
	else
	{
		if (ray->raydiry > 0)
			return (&data->north);
		else
			return (&data->south);
	}
}

static int	get_texture_x(t_data *data, t_ray *ray, t_texture *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = data->player.posy + ray->perpwalldist * ray->raydiry;
	else
		wall_x = data->player.posx + ray->perpwalldist * ray->raydirx;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->raydirx < 0)
		|| (ray->side == 1 && ray->raydiry > 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static void	draw_column_pixels(t_tex_draw_params *p)
{
	int			y;
	int			tex_y;
	int			index;
	uint32_t	color;

	y = p->ray->drawstart;
	while (y < p->ray->drawend)
	{
		tex_y = (int)p->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= p->tex->height)
			tex_y = p->tex->height - 1;
		index = (tex_y * p->tex->width + p->tex_x) * 4;
		color = ((uint32_t)p->tex->pixels[index] << 24)
			| ((uint32_t)p->tex->pixels[index + 1] << 16)
			| ((uint32_t)p->tex->pixels[index + 2] << 8)
			| ((uint32_t)p->tex->pixels[index + 3]);
		mlx_put_pixel(p->data->img, p->x, y, color);
		p->tex_pos += p->step;
		y++;
	}
}

void	draw_textured_column(t_data *data, int x, t_ray *ray)
{
	t_texture			*tex;
	int					tex_x;
	double				step;
	double				tex_pos;
	t_tex_draw_params	params;

	tex = get_texture(data, ray);
	tex_x = get_texture_x(data, ray, tex);
	step = 1.0 * tex->height / ray->lineheight;
	tex_pos = (ray->drawstart - (WIN_HEIGHT / 2)
			+ (ray->lineheight / 2)) * step;
	params.data = data;
	params.x = x;
	params.ray = ray;
	params.tex = tex;
	params.tex_x = tex_x;
	params.step = step;
	params.tex_pos = tex_pos;
	draw_column_pixels(&params);
}
