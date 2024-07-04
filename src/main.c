/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:28:24 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/05 00:51:09 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


int	main(int argc, char **argv)
{
	t_game	game;
	
	// game.last_x = WINDOW_WIDTH / 2;
	init(&game);
	parsing(&game, argc, argv);
	game.mlx = mlx_init();
	game.previous_time = get_time_in_seconds();
	if (!game.mlx)
		return (0);
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT + MINIMAP_SIZE * 20 + 4, WINDOW_NAME);
	if (!game.win)
		return (0);
	create_mlx_textures(&game);
	draw(&game);
	mlx_mouse_hide(game.mlx, game.win);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_loop_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
