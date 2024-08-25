/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:10:13 by asangerm          #+#    #+#             */
/*   Updated: 2024/08/25 19:11:28 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_wspace(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (0);
	return (1);
}

void	check_border(t_game *game, char **map, int i, int j)
{
	if (i == 0)
		ft_error(game, INVALID_MAP);
	if (i == game->map.height - 1)
		ft_error(game, INVALID_MAP);
	if (j == 0)
		ft_error(game, INVALID_MAP);
	if (j == (int)ft_strlen(map[i]) - 1)
		ft_error(game, INVALID_MAP);
}

void	check_position(t_game *game, char **map)
{
	int	i;
	int	j;

	i = game->player.y;
	j = game->player.x;
	if ((int)ft_strlen(map[i - 1]) < j || (int)ft_strlen(map[i + 1]) < j
		|| is_wspace(map[i][j - 1]) || is_wspace(map[i][j + 1])
		|| is_wspace(map[i - 1][j]) || is_wspace(map[i + 1][j]))
		ft_error(game, INVALID_MAP);
}

void	check_player(t_game *game, char **map)
{
	int	i;
	int	j;

	if (game->player.face_to == '0')
		ft_error(game, INVALID_MAP);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	check_position(game, map);
}

void	check_end(t_game *game)
{
	int	i;
	int	j;

	i = game->map.end_map;
	while (game->map.tab[i])
	{
		j = 0;
		while (game->map.tab[i][j])
		{
			if (game->map.tab[i][j] != ' ' && game->map.tab[i][j] != '\t'
				&& game->map.tab[i][j] != '\r' && game->map.tab[i][j] != '\n'
				&& game->map.tab[i][j] != '\v' && game->map.tab[i][j] != '\f')
				ft_error(game, INVALID_MAP);
			j++;
		}
		i++;
	}
}
