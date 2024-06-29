/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:28:24 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/29 18:38:14 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int key_press(int keycode, t_game *game)
{
	if (keycode== K_ECHAP)
		end(game);
	if (keycode== K_LEFT_ARROW)
		game->player.rota -= 1;
	if (keycode== K_RIGHT_ARROW)
		game->player.rota += 1;
	if (keycode== K_UP)
		game->player.moveY = 1;
	if (keycode== K_LEFT)
		game->player.moveX = -1;
	if (keycode== K_DOWN)
		game->player.moveY = -1;
	if (keycode== K_RIGHT)
		game->player.moveX = 1;
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode== K_ECHAP)
		end(game);
	if (keycode== K_UP && game->player.moveY == 1)
		game->player.moveY = 0;
	if (keycode== K_DOWN && game->player.moveY == -1)
		game->player.moveY = 0;
	if (keycode== K_LEFT && game->player.moveX == -1)
		game->player.moveX += 1;
	if (keycode== K_RIGHT && game->player.moveX == 1)
		game->player.moveX -= 1;
	if (keycode== K_LEFT_ARROW && game->player.rota <= 1)
		game->player.rota = 0;
	if (keycode== K_RIGHT_ARROW && game->player.rota >= -1)
		game->player.rota = 0;
	return (0);
}


int	main(int argc, char **argv)
{
	t_game	game;

	init(&game);
	parsing(&game, argc, argv);
    memset(game.keypressed, 0, sizeof(game.keypressed));
	game.mlx = mlx_init();
    game.previous_time = get_time_in_seconds();
	if (!game.mlx)
		return (0);
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, WINDOW_NAME);
	if (!game.win)
		return (0);
	draw(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_loop_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}