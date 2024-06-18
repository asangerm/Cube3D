/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:38:47 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/18 03:41:17 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	end(t_game *game)
{
	if (game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

int	close_window(t_game *game)
{
	end(game);
	return (0);
}

int	main()
{
	t_game	game;

	game.mlx = mlx_init();
	if (!game.mlx)
		return (0);
	game.win = mlx_new_window(game.mlx, 10 * 64,
			10 * 64, "Cube 3D");
	if (!game.win)
		return (0);
	tester();
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}