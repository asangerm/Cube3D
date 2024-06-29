/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:18:48 by nfradet           #+#    #+#             */
/*   Updated: 2024/06/28 13:56:18 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	get_time_in_seconds()
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return (ts.tv_sec + ts.tv_nsec / 1e9);
}

void	calculate_and_display_fps(t_game *game)
{
	char fps_str[32];

	game->current_time = get_time_in_seconds();
	game->frame_count++;
	if (game->current_time - game->previous_time >= 1.0)
	{
		game->fps = game->frame_count;
		game->frame_count = 0;
		game->previous_time = game->current_time;
	}
	sprintf(fps_str, "FPS: %d", game->fps);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, fps_str);
}