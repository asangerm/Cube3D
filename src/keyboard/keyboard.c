/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:49:50 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/29 18:40:12 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_up(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x + game->player.dirX * 0.01;
	next_y = game->player.y + game->player.dirY * 0.01;
	if (game->map.real_map[(int)next_y][(int)game->player.x] != '1')
		game->player.y = next_y;
	if (game->map.real_map[(int)game->player.y][(int)next_x] != '1')
		game->player.x = next_x;
}

void	move_down(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x - game->player.dirX * 0.01;
	next_y = game->player.y - game->player.dirY * 0.01;
	if (game->map.real_map[(int)next_y][(int)game->player.x] != '1')
		game->player.y = next_y;
	if (game->map.real_map[(int)game->player.y][(int)next_x] != '1')
		game->player.x = next_x;
}

void	move_left(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x + game->player.dirY * 0.01;
	next_y = game->player.y - game->player.dirX * 0.01;
	if (game->map.real_map[(int)next_y][(int)game->player.x] != '1')
		game->player.y = next_y;
	if (game->map.real_map[(int)game->player.y][(int)next_x] != '1')
		game->player.x = next_x;
}

void	move_right(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x - game->player.dirY * 0.01;
	next_y = game->player.y + game->player.dirX * 0.01;
	if (game->map.real_map[(int)next_y][(int)game->player.x] != '1')
		game->player.y = next_y;
	if (game->map.real_map[(int)game->player.y][(int)next_x] != '1')
		game->player.x = next_x;
}

void	rotate(t_game *game)
{
	double		rot;
	double		tmp;
	t_player	*p;

	if (game->player.rota == 0)
		return ;
	if (game->player.rota < 0)
		rot = -0.01;
	else if (game->player.rota > 0)
		rot = 0.01;
	else
		return ;
	p = &(game->player);
	
	tmp = p->dirX;
	p->dirX = p->dirX * cos(rot) - p->dirY * sin(rot);
	p->dirY = tmp * sin(rot) + p->dirY * cos(rot);
	tmp = p->planeX;
	p->planeX = p->planeX * cos(rot) - p->planeY * sin(rot);
	p->planeY = tmp * sin(rot) + p->planeY * cos(rot);
}

int	key_hook(t_game *game)
{
	if (game->player.moveY == 1)
		move_up(game);
	if (game->player.moveY == -1)
		move_down(game);
	if (game->player.moveX == -1)
		move_left(game);
	if (game->player.moveX == 1)
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
