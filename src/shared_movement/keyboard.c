/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:49:50 by asangerm          #+#    #+#             */
/*   Updated: 2024/08/24 18:48:03 by nfradet          ###   ########.fr       */
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

void	rotate(t_game *game)
{
	double		rot;
	double		tmp;
	t_player	*p;

	if (game->player.rota == 0)
		return ;
	if (game->player.rota < 0)
		rot = -MOVE_SPEED;
	else if (game->player.rota > 0)
		rot = MOVE_SPEED;
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

int	close_window(t_game *game)
{
	end(game);
	return (0);
}
