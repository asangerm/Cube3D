/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:38:47 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/29 17:14:10 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int key_press(int keycode, t_game *game)
{
	// ft_printf("key pressed : %d\n", keycode);
	if (keycode < 256)
		game->keypressed[keycode] = 1;
	if (keycode == K_LEFT_ARROW)
		game->keyrotated[0] = 1;
	if (keycode == K_RIGHT_ARROW)
		game->keyrotated[1] = 1;
	key_hook(keycode, game);
	return (0);
}

int key_release(int keycode, t_game *game)
{
	// ft_printf("key release : %d\n", keycode);
	if (keycode < 256)
		game->keypressed[keycode] = 0;
	if (keycode == K_LEFT_ARROW)
		game->keyrotated[0] = 0;
	if (keycode == K_RIGHT_ARROW)
		game->keyrotated[1] = 0;
	// key_hook(keycode, game);
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
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	// mlx_hook(game.win, 2, 1L<<0, key_hook, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	//draw_map(&game, 0, 0);
	mlx_loop_hook(game.mlx, draw, &game);
	// draw(&game);
	mlx_loop(game.mlx);
	return (0);
}
