/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:02:00 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/02 14:53:40 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	player_start_2(t_player *player)
{
	if (player->face_to == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->face_to == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	player_start(t_player *player)
{
	if (player->dir_x != 0 || player->dir_y != 0
		|| player->plane_x != 0 || player->plane_y != 0)
		return ;
	if (player->face_to == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->face_to == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
		player_start_2(player);
}
