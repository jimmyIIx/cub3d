/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:39:47 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/29 12:30:05 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/libft/libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include "MLX42.h"

# define WIN_WIDTH	1024
# define WIN_HEIGHT	768
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOVESPEED 0.05
# define ROTSPEED 0.03

typedef enum e_config_type
{
	NONE,
	NO,
	SO,
	WE,
	EA,
	F,
	C
}				t_config_type;

// STRUCTURE PLAYER and ...
typedef struct s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	int			rotate;
	int			move_x;
	int			move_y;
	int			has_moved;
	bool		has_player;
}				t_player;

// CAMERA
typedef struct s_ray
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
}				t_ray;

// CONFIG
typedef struct s_config
{
	uint8_t		*no_pix;
	uint8_t		*so_pix;
	uint8_t		*we_pix;
	uint8_t		*ea_pix;
	int			floor[3];
	int			ceiling[3];
	bool		no_set;
	bool		so_set;
	bool		we_set;
	bool		ea_set;
	bool		floor_set;
	bool		ceiling_set;
}				t_config;

typedef struct s_li
{
	char		*ln;
	char		*b_l;
	char		*n_l;
}				t_li;

typedef struct s_pl
{
	bool		player;
	double		player_x;
	double		player_y;
	char		player_orientation;
}				t_pl;

typedef struct s_map
{
	char		**map;
	size_t		max_rows;
	size_t		max_cols;
	char		*buffer;
	bool		maping;
	bool		complet;
	t_li		li;
	t_pl		pl;
}				t_map;

typedef struct s_texture
{
	uint8_t		*pixels;
	int			width;
	int			height;
}				t_texture;

typedef struct s_data
{
	mlx_image_t		*img;
	mlx_t			*mlx;
	t_config		config;
	t_map			map;
	t_player		player;
	t_ray			ray;
	t_texture		north;
	t_texture		south;
	t_texture		west;
	t_texture		east;
	int				line_length;
	int				endian;
	int				win_width;
	int				win_height;
	void			*win;
}					t_data;

typedef struct s_tex_draw_params
{
	t_data		*data;
	t_ray		*ray;
	t_texture	*tex;
	int			x;
	int			tex_x;
	double		step;
	double		tex_pos;
}	t_tex_draw_params;

bool	parsing(int argc, char **argv, t_data *data);
bool	parse_args(int argc, char **argv);
bool	parse_config(t_config *config, int fd);
bool	stock_pix(t_config *config, t_config_type	type, char *line);
bool	stock_rgb(t_config *config, t_config_type	type, char *line);
bool	parse_map(t_map *map, int fd);
bool	stock_map(t_map *map, char *line, char *before_line, char *next_line);
bool	check_map(t_map *map, char *line, char *before_line, char *next_line);
void	raycasting_loop(t_data *data);
void	draw_textured_column(t_data *data, int x, t_ray *ray);
void	update_and_render(void *param);
int		validate_move(t_data *data, double new_x, double new_y);
int		move_player(t_data *data);
int		rotate_player(t_data *data, double rotdir);
void	print_menu(t_data *data);
void	on_close(void *param);
bool	init_game(t_data *data);
size_t	ft_tablen(char **tab);
char	*ft_strcpy(char *dest, const char *src);
void	init_data(t_data *data);
void	clear_data(t_data *data);
void	init_config(t_config *config);
void	clear_config(t_config *config);
void	init_map(t_map *map);
void	clear_map(t_map *map);
void	init_player(t_player *player);
void	clear_player(t_player *player);
void	init_ray(t_ray *ray);
void	clear_ray(t_ray *ray);
void	init_li(t_li *li);
void	init_pl(t_pl *pl);
void	clear_pl(t_pl *pl);
void	init_textures(t_data *data);

#endif
