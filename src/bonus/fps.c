/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:18:48 by nfradet           #+#    #+#             */
/*   Updated: 2024/07/27 13:26:15 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double	get_time_in_seconds(void)
{
	struct timespec	ts;

	timespec_get(&ts, TIME_UTC);
	return (ts.tv_sec + ts.tv_nsec / 1e9);
}

void	calculate_and_display_fps(t_game *game)
{
	char	fps_str[32];

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

void	heart_hud(t_game *game)
{
	t_image	heart;
	int		i;
	int		start;
	int		life;

	start = MINIMAP_SIZE * TILE_SIZE + BORDER_SIZE * 2;
	i = 0;
	life = 8;
	heart.img = mlx_xpm_file_to_image(game->mlx, HEART_PATH, &(heart.width),
			&(heart.height));
	while (i < life)
	{
		mlx_put_image_to_window(game->mlx, game->win, heart.img, start
			+ i * (heart.width + 5) + 5, GAME_HEIGHT);
		i++;
	}
	mlx_destroy_image(game->mlx, heart.img);
}
