/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:19:43 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/25 19:09:37 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	check_middle(t_game *game, int i, int j)
{
	char	**map;

	map = game->map.real_map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW0", map[i][j]) != NULL)
			{
				if (i == 0 || i == game->map.height - 1 || j == 0
					|| j == (int)ft_strlen(map[i]) - 1)
					check_border(game, game->map.real_map, i, j);
				else
					check_center(game, game->map.real_map, i, j);
			}
			j++;
		}
		i++;
	}
}

void	check_center(t_game *game, char **map, int i, int j)
{
	if (!map[i - 1][j] || ft_strchr("NSEW10", map[i - 1][j]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i + 1][j] || ft_strchr("NSEW10", map[i + 1][j]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i][j - 1] || ft_strchr("NSEW10", map[i][j - 1]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i][j + 1] || ft_strchr("NSEW10", map[i][j + 1]) == NULL)
		ft_error(game, INVALID_MAP);
}

void	parsing(t_game *game, int argc, char **argv)
{
	arg_checker(game, argc, argv);
	map_extractor(game);
	get_data(game);
	data_checker(game);
}

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
