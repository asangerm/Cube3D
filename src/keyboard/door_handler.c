/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:07:18 by nfradet           #+#    #+#             */
/*   Updated: 2024/07/15 03:30:17 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	close_door_if(t_game *game)
{
	char	**map;
	int		x;
	int		y;

	x = 0;
	map = game->map.real_map;
	while (map[x])
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			if (map[x][y] == 'O')
			{
				if (sqrt(power(game->player.y - x + 0.5)
						+ power(game->player.x - y + 0.5)) >= 2)
					map[x][y] = 'C';
			}
			y++;
		}
		x++;
	}
}

void	open_door(t_game *game)
{
	char	**map;
	int		x;
	int		y;

	close_door_if(game);
	map = game->map.real_map;
	x = (int)game->player.x;
	y = (int)game->player.y;
	if (map[y + 1][x] == 'C')
		map[y + 1][x] = 'O';
	if (map[y - 1][x] == 'C')
		map[y - 1][x] = 'O';
	if (map[y][x + 1] == 'C')
		map[y][x + 1] = 'O';
	if (map[y][x - 1] == 'C')
		map[y][x - 1] = 'O';
}
