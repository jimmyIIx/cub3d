/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_pix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:16:15 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 16:35:21 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	load_and_set(uint8_t **pix, bool *set_flag, char *line);
static bool	load_texture(uint8_t **dest, char *raw_line, size_t prefix_len);
static bool	is_valid_texture_path(const char *path);

bool	stock_pix(t_config *config, t_config_type	type, char *line)
{
	if (type == NO)
		return (load_and_set(&config->no_pix, &config->no_set, line));
	if (type == SO)
		return (load_and_set(&config->so_pix, &config->so_set, line));
	if (type == WE)
		return (load_and_set(&config->we_pix, &config->we_set, line));
	if (type == EA)
		return (load_and_set(&config->ea_pix, &config->ea_set, line));
	return (false);
}

static bool	load_and_set(uint8_t **pix, bool *set_flag, char *line)
{
	if (*set_flag)
		return (false);
	if (!load_texture(pix, line, 3))
		return (false);
	*set_flag = true;
	return (true);
}

static bool	load_texture(uint8_t **dest, char *raw_line, size_t prefix_len)
{
	char			*path;
	size_t			size;
	mlx_texture_t	*tex;

	if (!dest || !raw_line)
		return (false);
	path = ft_strtrim(raw_line + prefix_len, " \t\n\r");
	if (!is_valid_texture_path(path))
		return (free(path), false);
	tex = mlx_load_png(path);
	if (!tex)
		return (free(path), false);
	if (tex->width != TEX_WIDTH || tex->height != TEX_HEIGHT)
		return (mlx_delete_texture(tex), free(path), false);
	size = tex->width * tex->height * 4;
	*dest = malloc(size * sizeof(uint8_t));
	if (!*dest)
		return (mlx_delete_texture(tex), free(path), false);
	ft_memcpy(*dest, tex->pixels, size);
	mlx_delete_texture(tex);
	free(path);
	return (true);
}

static bool	is_valid_texture_path(const char *path)
{
	size_t	len;

	if (!path)
		return (false);
	len = ft_strlen(path);
	if (len < 5)
		return (false);
	if (path[len - 4] != '.'
		|| path[len - 3] != 'p'
		|| path[len - 2] != 'n'
		|| path[len - 1] != 'g')
		return (false);
	if (access(path, F_OK) != 0 || access(path, R_OK) != 0)
		return (false);
	return (true);
}
