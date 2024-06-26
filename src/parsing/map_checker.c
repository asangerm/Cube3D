/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:10:13 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/26 22:21:10 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	check_char(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\r'
			|| map[i][j] == '\v' || map[i][j] == '\f')
				j++;
			if (map[i][j])
			{
				if (!(ft_strchr("10NSEW", map[i][j])))
					ft_error(game, INVALID_MAP);
				if (ft_strchr("NSEW", map[i][j]) && game->player.face_to != '0')
					ft_error(game, INVALID_MAP);
				if (ft_strchr("NSEW", map[i][j]) && game->player.face_to == '0')
					game->player.face_to = map[i][j];
				j++;
			}
		}
		i++;
	}
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

void	map_checker(t_game *game)
{
	if (!game->map.real_map)
		ft_error(game, INVALID_MAP);
	if (game->map.height < 3)
		ft_error(game, INVALID_MAP);
	check_char(game, game->map.real_map);
	check_player(game, game->map.real_map);
	check_end(game);
	check_middle(game, 0, 0);
}
