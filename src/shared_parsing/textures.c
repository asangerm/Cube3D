/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:38:33 by asangerm          #+#    #+#             */
/*   Updated: 2024/08/24 00:23:13 by nfradet          ###   ########.fr       */
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

