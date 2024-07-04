/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:49:50 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/05 00:31:43 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// void	handle_cursor_limit(t_game *game, int x, int y)
// {
// 	(void) y;
// 	if (x > WINDOW_WIDTH - 20)
// 	{
// 		x = 20;
// 		mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
// 		game->last_x = x;
// 	}
// 	else if (x < 20)
// 	{
// 		x = WINDOW_WIDTH - 20;
// 		mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
// 		game->last_x = x;
// 	}
// }

// int	mouse_move(int x, int y, t_game *game)
// {
// 	(void) y;
// 	ft_printf("x : %d\n",x);
// 	ft_printf("last_x : %d\n",game->last_x);
// 	if (x == game->last_x)
//         return (0);
// 	handle_cursor_limit(game, x, y);
// 	if (x < game->last_x)
// 		game->player.rota = -1;
// 	else if (x > game->last_x)
// 		game->player.rota = 1;
// 	game->last_x = x;
// 	game->is_rota_stopping = 1;
// 	return (0);
// }

int	mouse_move(int x, int y, t_game *game)
{
	int		diff_x;
	int		limit;
	// double	ms;
	
	if (x > (WINDOW_WIDTH / 2) + 20)
		limit = (WINDOW_WIDTH / 2) + 20;
	else if (x < (WINDOW_WIDTH / 2) - 20)
		limit = (WINDOW_WIDTH / 2) - 20;
	else
		limit = x;

	
	diff_x = x - limit;
	// ft_printf("x = %d\n", x);
	// ft_printf("diff = %d\n", diff_x);
	if (diff_x < 0)
		game->player.rota = -1;
	else if (diff_x > 0)
		game->player.rota = 1;
	else
		game->player.rota = 0;
	if (x >= WINDOW_WIDTH - 20 || x <= 20)
		game->player.rota = 0;
	else if (y > WINDOW_HEIGHT - 50 || y < 50)
		game->player.rota = 0;
	game->move_speed = abs(diff_x) / COEFF_MOUSE_ROTA;
	printf("ms = %f\n",(double) (abs(diff_x) / COEFF_MOUSE_ROTA));
	
	return (0);
}

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
	// if (game->is_rota_stopping == 1)
	// {
	// 	game->player.rota = 0;
	// 	game->is_rota_stopping = 0;
	// }
	draw(game);
	return (0);
}

int	close_window(t_game *game)
{
	end(game);
	return (0);
}
