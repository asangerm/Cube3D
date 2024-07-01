/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:49:50 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/01 23:32:48 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == K_ECHAP)
		end(game);
	if (keycode == K_LEFT_ARROW)
		game->player.rota -= 1;
	if (keycode == K_RIGHT_ARROW)
		game->player.rota += 1;
	if (keycode == K_UP)
		game->player.move_y = 1;
	if (keycode == K_LEFT)
		game->player.move_x = -1;
	if (keycode == K_DOWN)
		game->player.move_y = -1;
	if (keycode == K_RIGHT)
		game->player.move_x = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == K_ECHAP)
		end(game);
	if (keycode == K_UP && game->player.move_y == 1)
		game->player.move_y = 0;
	if (keycode == K_DOWN && game->player.move_y == -1)
		game->player.move_y = 0;
	if (keycode == K_LEFT && game->player.move_x == -1)
		game->player.move_x += 1;
	if (keycode == K_RIGHT && game->player.move_x == 1)
		game->player.move_x -= 1;
	if (keycode == K_LEFT_ARROW && game->player.rota <= 1)
		game->player.rota = 0;
	if (keycode == K_RIGHT_ARROW && game->player.rota >= -1)
		game->player.rota = 0;
	return (0);
}

int	key_hook(t_game *game)
{
	if (game->player.move_y == 1)
		move_up(game);
	if (game->player.move_y == -1)
		move_down(game);
	if (game->player.move_x == -1)
		move_left(game);
	if (game->player.move_x == 1)
		move_right(game);
	if (game->player.rota != 0)
		rotate(game);
	draw(game);
	return (0);
}

int	close_window(t_game *game)
{
	end(game);
	return (0);
}
