/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:44:24 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/25 19:00:37 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_up(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x + game->player.dir_x * (MOVE_SPEED);
	next_y = game->player.y + game->player.dir_y * (MOVE_SPEED);
	if (!(ft_strchr("1C",
				game->map.real_map
				[(int)(next_y + 0.2 * get_sign(game->player.dir_y))]
			[(int)game->player.x])))
		game->player.y = next_y;
	if (!(ft_strchr("1C",
				game->map.real_map
				[(int)game->player.y]
				[(int)(next_x + 0.2 * get_sign(game->player.dir_x))])))
		game->player.x = next_x;
}

void	move_down(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	next_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (!(ft_strchr("1C",
				game->map.real_map
				[(int)(next_y - 0.2 * get_sign(game->player.dir_y))]
			[(int)game->player.x])))
		game->player.y = next_y;
	if (!(ft_strchr("1C",
				game->map.real_map
				[(int)game->player.y]
				[(int)(next_x - 0.2 * get_sign(game->player.dir_x))])))
		game->player.x = next_x;
}

void	move_left(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x + game->player.dir_y * MOVE_SPEED;
	next_y = game->player.y - game->player.dir_x * MOVE_SPEED;
	if (!(ft_strchr("1C",
				game->map.real_map
				[(int)(next_y - 0.2 * get_sign(game->player.dir_x))]
			[(int)game->player.x])))
		game->player.y = next_y;
	if (!(ft_strchr("1C",
				game->map.real_map
				[(int)game->player.y]
				[(int)(next_x + 0.2 * get_sign(game->player.dir_y))])))
		game->player.x = next_x;
}

void	move_right(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x - game->player.dir_y * MOVE_SPEED;
	next_y = game->player.y + game->player.dir_x * MOVE_SPEED;
	if (!(ft_strchr("1C",
				game->map.real_map
				[(int)(next_y + 0.2 * get_sign(game->player.dir_x))]
			[(int)game->player.x])))
		game->player.y = next_y;
	if (!(ft_strchr("1C",
				game->map.real_map
				[(int)game->player.y]
				[(int)(next_x - 0.2 * get_sign(game->player.dir_y))])))
		game->player.x = next_x;
}

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
