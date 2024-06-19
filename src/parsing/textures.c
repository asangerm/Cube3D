/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:38:33 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/19 18:34:11 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*get_path(char *line, int j)
{
	int		l;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	l = j;
	while (line[l] && (line[l] != ' ' && line[l] != '\t'))
		l++;
	path = malloc(sizeof(char) * (l - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

void	get_textures(t_game *game, t_info *info, char *line, int j)
{
	if (line[j + 2] && ft_isprint(line[j + 2]))
		ft_error(game, INVALID_TEXT);
	if (line[j] == 'N' && line[j + 1] == 'O' && !(info->no_path))
		info->no_path = get_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(info->so_path))
		info->so_path = get_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(info->we_path))
		info->we_path = get_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(info->ea_path))
		info->ea_path = get_path(line, j + 2);
	else
		ft_error(game, INVALID_TEXT);
}

void	check_path(t_game *game, char *path)
{
	char	**split_path;
	int		fd;

	split_path = ft_split(path, '.');
	if (split_len(split_path) != 2)
	{
		free_tab(split_path);
		ft_error(game, INVALID_TEXT);
	}
	if (ft_strncmp("xpm", split_path[1], 4) != 0)
	{
		free_tab(split_path);
		ft_error(game, INVALID_TEXT);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free_tab(split_path);
		ft_error(game, INVALID_TEXT);
	}
	free_tab(split_path);
	close(fd);
}

void	texture_checker(t_game *game)
{
	t_info	info;

	info = game->map.map_info;
	if (!info.no_path || !info.so_path || !info.ea_path || !info.we_path)
		ft_error(game, INVALID_TEXT);
	if (!info.c_color || !info.f_color)
		ft_error(game, INVALID_COLOR);
	check_path(game, info.ea_path);
	check_path(game, info.no_path);
	check_path(game, info.so_path);
	check_path(game, info.we_path);
}

void	data_checker(t_game *game)
{
	texture_checker(game);
	color_checker(game);
	//map_checker(game);
}