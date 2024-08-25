/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:00:48 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/25 02:18:18 by nfradet          ###   ########.fr       */
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

void	draw_line(t_game *game, int x)
{
	int		i;
	t_list	*iter;
	t_ray	*cur_ray;

	iter = game->lst_ray;
	while (iter != NULL)
	{
		i = 0;
		cur_ray = (t_ray *)iter->content;
		while (i < GAME_HEIGHT)
		{
			if (i >= 0 && i < cur_ray->start)
				game->tab_img[i][x] = color_change(game->map.map_info.c_color);
			else if (i >= cur_ray->start && i <= cur_ray->end)
			{
				handle_textures(game, cur_ray, x);
				i = cur_ray->end;
			}
			else if (i > cur_ray->end && i < GAME_HEIGHT)
				game->tab_img[i][x] = color_change(game->map.map_info.f_color);
			i++;
		}
		iter = iter->next;
	}
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
