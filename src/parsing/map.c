/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:32:34 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/21 15:56:30 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	map_extractor(t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(game->map.fd);
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(game->map.fd);
	}
	free(line);
	close(game->map.fd);
	game->map.fd = open(game->map.path, O_RDONLY);
	game->map.tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	line = get_next_line(game->map.fd);
	while (line)
	{
		game->map.tab[i] = line;
		i++;
		line = get_next_line(game->map.fd);
	}
	game->map.tab[i] = (void *)0;
	close(game->map.fd);
}

void	set_map(t_game *game, t_map *m, char **map, int w)
{
	int		i;
	int		j;

	m->width = get_width(m, w);
	i = 0;
	while (i < m->height)
	{
		j = 0;
		map[i] = malloc(sizeof(char) * (m->width + 1));
		if (!map[i])
			ft_error(game, INVALID_MAP);
		while (m->tab[w][j] && m->tab[w][j] != '\n')
		{
			map[i][j] = m->tab[w][j];
			j++;
		}
		while (j < m->width)
			map[i][j++] = '\0';
		i++;
		w++;
	}
	map[i] = NULL;
}

void	get_map(t_game *game, char **map, int i)
{
	game->map.height = get_height(game, map, i);
	game->map.real_map = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.real_map)
		ft_error(game, INVALID_MAP);
	set_map(game, &game->map, game->map.real_map, i);
}
