/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:46:32 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/25 19:07:45 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	can_i_go(t_game *game, int next_y, int next_x)
{
	if (!ft_strchr("01", game->map.real_map[next_y][next_x]))
		return (0);
	if (!ft_strchr("01", game->map.real_map[next_y + 1][next_x]))
		return (0);
	if (!ft_strchr("01", game->map.real_map[next_y - 1][next_x]))
		return (0);
	if (!ft_strchr("01", game->map.real_map[next_y][next_x + 1]))
		return (0);
	if (!ft_strchr("01", game->map.real_map[next_y][next_x - 1]))
		return (0);
	return (1);
}

void	move_up(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x + game->player.dir_x * (MOVE_SPEED);
	next_y = game->player.y + game->player.dir_y * (MOVE_SPEED);
	if ((int)(next_y + 0.2 * get_sign(game->player.dir_y)) > 0 && \
		(int)(next_y + 0.2 * get_sign(game->player.dir_y)) \
		< game->map.height - 1)
	{
		if (can_i_go(game, (int)(next_y + 0.2 * \
			get_sign(game->player.dir_y)), \
			(int)game->player.x) == 1)
			game->player.y = next_y;
	}
	if ((int)(next_x + 0.2 * get_sign(game->player.dir_x)) > 0 && \
		(int)(next_x + 0.2 * get_sign(game->player.dir_x)) \
		< game->map.width - 1)
	{
		if (can_i_go(game, \
			(int)game->player.y, \
			(int)(next_x + 0.2 * get_sign(game->player.dir_x))) == 1)
			game->player.x = next_x;
	}
}

void	move_down(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	next_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if ((int)(next_y - 0.2 * get_sign(game->player.dir_y)) > 0 && \
		(int)(next_y - 0.2 * get_sign(game->player.dir_y)) \
		< game->map.height - 1)
	{
		if (can_i_go(game, \
			(int)(next_y - 0.2 * get_sign(game->player.dir_y)), \
			(int)game->player.x) == 1)
			game->player.y = next_y;
	}
	if ((int)(next_x - 0.2 * get_sign(game->player.dir_x)) > 0 && \
		(int)(next_x - 0.2 * get_sign(game->player.dir_x)) \
		< game->map.width - 1)
	{
		if (can_i_go(game, \
			(int)game->player.y, \
			(int)(next_x - 0.2 * get_sign(game->player.dir_x))) == 1)
			game->player.x = next_x;
	}
}

void	move_left(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x + game->player.dir_y * MOVE_SPEED;
	next_y = game->player.y - game->player.dir_x * MOVE_SPEED;
	if ((int)(next_y - 0.2 * get_sign(game->player.dir_x)) > 0 && \
		(int)(next_y - 0.2 * get_sign(game->player.dir_x)) \
		< game->map.height - 1)
	{
		if (can_i_go(game, \
			(int)(next_y - 0.2 * get_sign(game->player.dir_x)), \
			(int)game->player.x) == 1)
			game->player.y = next_y;
	}
	if ((int)(next_x + 0.2 * get_sign(game->player.dir_y)) > 0 &&
		(int)(next_x + 0.2 * get_sign(game->player.dir_y)) \
		< game->map.width - 1)
	{
		if (can_i_go(game, \
			(int)game->player.y, \
			(int)(next_x + 0.2 * get_sign(game->player.dir_y))) == 1)
			game->player.x = next_x;
	}
}

void	move_right(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x - game->player.dir_y * MOVE_SPEED;
	next_y = game->player.y + game->player.dir_x * MOVE_SPEED;
	if ((int)(next_y + 0.2 * get_sign(game->player.dir_x)) > 0 && \
		(int)(next_y + 0.2 * get_sign(game->player.dir_x)) \
		< game->map.height - 1)
	{
		if (can_i_go(game, \
			(int)(next_y + 0.2 * get_sign(game->player.dir_x)), \
			(int)game->player.x) == 1)
			game->player.y = next_y;
	}
	if ((int)(next_x - 0.2 * get_sign(game->player.dir_y)) > 0 && \
		(int)(next_x - 0.2 * get_sign(game->player.dir_y)) \
		< game->map.width - 1)
	{
		if (can_i_go(game, \
			(int)game->player.y, \
			(int)(next_x - 0.2 * get_sign(game->player.dir_y))) == 1)
			game->player.x = next_x;
	}
}
