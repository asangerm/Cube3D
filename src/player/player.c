/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:02:00 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/24 16:26:25 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	player_init_2(t_player *player)
{
	if (player->face_to == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = 0.66;
	}
	else if (player->face_to == 'W')
	{
		player->dirX = -1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = -0.66;
	}
}

void	player_init(t_player *player)
{
	if (player->face_to == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
		player->planeX = 0.66;
		player->planeY = 0;
	}
	else if (player->face_to == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
		player->planeX = -0.66;
		player->planeY = 0;
	}
	else
		player_init_2(player);
}
