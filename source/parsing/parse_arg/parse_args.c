/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nippolit <nippolit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:39:02 by nippolit          #+#    #+#             */
/*   Updated: 2025/06/27 16:42:48 by nippolit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	has_cub_extension(char *filename);

bool	parse_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error:\nParsing: Number of arguments\n", 2);
		return (false);
	}
	if (!has_cub_extension(argv[1]))
	{
		ft_putstr_fd("Error:\nParsing: Extension .cub\n", 2);
		return (false);
	}
	return (true);
}

static bool	has_cub_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (false);
	if (filename[len - 4] != '.'
		|| filename[len - 3] != 'c'
		|| filename[len - 2] != 'u'
		|| filename[len - 1] != 'b')
		return (false);
	return (true);
}
