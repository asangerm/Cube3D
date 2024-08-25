/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:00:48 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/24 18:31:17 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	if (game->is_rota_stopping == 1)
	{
		game->player.rota = 0;
		game->is_rota_stopping = 0;
	}
	draw(game);
	return (0);
}

int	draw(t_game *game)
{
	int	i;

	game->tab_img = malloc((GAME_HEIGHT + 1) * sizeof(int *));
	i = 0;
	while (i < GAME_HEIGHT)
	{
		game->tab_img[i] = malloc((GAME_WIDTH + 1)
				* sizeof(int));
		i++;
	}
	raycasting(game, 0);
	free_star(game->tab_img, GAME_HEIGHT);
	return (0);
}
