/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:07:18 by nfradet           #+#    #+#             */
/*   Updated: 2024/07/16 18:27:38 by nfradet          ###   ########.fr       */
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
