/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:35:20 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/24 18:12:14 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	op_or_close_door(t_game *game)
{
	char	**map;
	int		x;
	int		y;
	double	len;

	x = 0;
	map = game->map.real_map;
	while (map[x])
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			if (map[x][y] == 'O' || map[x][y] == 'C')
			{
				len = sqrt(power(game->player.y - (x + 0.5))
						+ power(game->player.x - (y + 0.5)));
				if (len >= 2)
					map[x][y] = 'C';
				else if (len < 2)
					map[x][y] = 'O';
			}
			y++;
		}
		x++;
	}
}

int	check_corridor(t_game *game, int i, int j)
{
	char	**map;

	map = game->map.real_map;
	if (ft_strchr("10", map[i + 1][j]) == NULL)
		return (0);
	if (ft_strchr("10", map[i - 1][j]) == NULL)
		return (0);
	if (ft_strchr("10", map[i][j + 1]) == NULL)
		return (0);
	if (ft_strchr("10", map[i][j - 1]) == NULL)
		return (0);
	if (map[i][j + 1] == map[i + 1][j])
		return (0);
	if (map[i][j - 1] == map[i + 1][j])
		return (0);
	if (map[i][j + 1] == map[i - 1][j])
		return (0);
	if (map[i][j - 1] == map[i - 1][j])
		return (0);
	return (1);
}

void	check_doors(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.real_map[i])
	{
		j = 0;
		while (game->map.real_map[i][j] != '\0')
		{
			if (game->map.real_map[i][j] == 'O')
				game->map.real_map[i][j] = 'C';
			if (game->map.real_map[i][j] == 'C')
			{
				if (check_corridor(game, i, j) == 0)
					ft_error(game, INVALID_DOOR);
			}
			j++;
		}
		i++;
	}
}
