/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:38:47 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/24 01:47:27 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	init(&game);
	parsing(&game, argc, argv);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (0);
	game.win = mlx_new_window(game.mlx, 640,
			480, WINDOW_NAME);
	if (!game.win)
		return (0);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	draw_map(&game, 0, 0);
	mlx_loop(game.mlx);
	return (0);
}
