/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:58:12 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/05 18:28:03 by nfradet          ###   ########.fr       */
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

void	check_center(t_game *game, char **map, int i, int j)
{
	if (!map[i - 1][j] || ft_strchr("NSEW10CO", map[i - 1][j]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i + 1][j] || ft_strchr("NSEW10CO", map[i + 1][j]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i][j - 1] || ft_strchr("NSEW10CO", map[i][j - 1]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i][j + 1] || ft_strchr("NSEW10CO", map[i][j + 1]) == NULL)
		ft_error(game, INVALID_MAP);
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

void	check_middle(t_game *game, int i, int j)
{
	char	**map;

	map = game->map.real_map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW0CO", map[i][j]) != NULL)
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
