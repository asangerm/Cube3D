/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:49:50 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/11 22:35:19 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	int	mid_width;

	mid_width = (GAME_WIDTH / 2);
	(void) y;
	if (x - mid_width == 0)
		return (0);
	if (x - mid_width < 0)
		game->player.rota = -1;
	else if (x - mid_width > 0)
		game->player.rota = 1;
	mlx_mouse_move(game->mlx, game->win, mid_width, GAME_HEIGHT / 2);
	game->is_rota_stopping = 1;
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	printf("key pressed %d\n", keycode);
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
	printf("key released %d\n", keycode);
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

void	close_door_if(t_game *game)
{
	char	**map;
	int	x;
	int	y;

	x = 0;
	map = game->map.real_map;
	while (map[x])
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			if (map[x][y] == 'O')
			{
				if (map[(int)game->player.y][(int)game->player.x] != 'O' &&
					map[(int)game->player.y + 1][(int)game->player.x] != 'O' &&
					map[(int)game->player.y - 1][(int)game->player.x] != 'O' &&
					map[(int)game->player.y][(int)game->player.x + 1] != 'O' &&
					map[(int)game->player.y][(int)game->player.x - 1] != 'O')
					map[x][y] = 'C';
			}
			y++;
		}
		x++;
	}
}

void	open_door(t_game *game)
{
	char	**map;
	int		x;
	int		y;

	close_door_if(game);
	map = game->map.real_map;
	x = (int)game->player.x;
	y = (int)game->player.y;
	if (map[y + 1][x] == 'C')
		map[y + 1][x] = 'O';
	if (map[y - 1][x] == 'C')
		map[y - 1][x] = 'O';
	if (map[y][x + 1] == 'C')
		map[y][x + 1] = 'O';
	if (map[y][x - 1] == 'C')
		map[y][x - 1] = 'O';
}

int	key_hook(t_game *game)
{
	open_door(game);
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
	if (game->is_rota_stopping == 1)
	{
		game->player.rota = 0;
		game->is_rota_stopping = 0;
	}
	draw(game);
	return (0);
}

int	close_window(t_game *game)
{
	end(game);
	return (0);
}
