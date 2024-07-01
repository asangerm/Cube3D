/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:31:13 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/01 23:31:37 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_up(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x + game->player.dir_x * 0.01;
	next_y = game->player.y + game->player.dir_y * 0.01;
	if (game->map.real_map[(int)next_y][(int)game->player.x] != '1')
		game->player.y = next_y;
	if (game->map.real_map[(int)game->player.y][(int)next_x] != '1')
		game->player.x = next_x;
}

void	move_down(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x - game->player.dir_x * 0.01;
	next_y = game->player.y - game->player.dir_y * 0.01;
	if (game->map.real_map[(int)next_y][(int)game->player.x] != '1')
		game->player.y = next_y;
	if (game->map.real_map[(int)game->player.y][(int)next_x] != '1')
		game->player.x = next_x;
}

void	move_left(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x + game->player.dir_y * 0.01;
	next_y = game->player.y - game->player.dir_x * 0.01;
	if (game->map.real_map[(int)next_y][(int)game->player.x] != '1')
		game->player.y = next_y;
	if (game->map.real_map[(int)game->player.y][(int)next_x] != '1')
		game->player.x = next_x;
}

void	move_right(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x - game->player.dir_y * 0.01;
	next_y = game->player.y + game->player.dir_x * 0.01;
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
	tmp = p->dir_x;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = tmp * sin(rot) + p->dir_y * cos(rot);
	tmp = p->plane_x;
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = tmp * sin(rot) + p->plane_y * cos(rot);
}
