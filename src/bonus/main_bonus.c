/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:28:24 by asangerm          #+#    #+#             */
/*   Updated: 2024/08/24 18:08:55 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_map_bonus(t_map *map)
{
	map->split_path = NULL;
	map->fd = -1;
	map->height = 0;
	map->path = NULL;
	map->tab = NULL;
	map->real_map = NULL;
	map->width = 0;
	map->end_map = 0;
	init_info_bonus(&map->map_info);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_bonus(&game);
	parsing_bonus(&game, argc, argv);
	game.mlx = mlx_init();
	game.previous_time = get_time_in_seconds();
	if (!game.mlx)
		return (0);
	game.win = mlx_new_window(game.mlx, GAME_WIDTH, GAME_HEIGHT + MINIMAP_SIZE
			* TILE_SIZE + 2 * BORDER_SIZE, WINDOW_NAME);
	if (!game.win)
		return (0);
	create_mlx_textures_bonus(&game);
	draw(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_loop_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
