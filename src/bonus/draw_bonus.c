/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:47:39 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/28 19:10:42 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	dark_circle(t_game *game)
{
	int		i;
	int		j;
	double	dist;
	double	max_dist;

	i = 0;
	max_dist = sqrt(power(0 - GAME_WIDTH / 2) + power(0 - GAME_HEIGHT / 2));
	while (i < GAME_HEIGHT)
	{
		j = 0;
		while (j < GAME_WIDTH)
		{
			dist = sqrt(power(j - GAME_WIDTH / 2) + power(i - GAME_HEIGHT / 2));
			dist = 0.00 + (1.0 - 0.00) * power(1 - (dist / max_dist));
			game->tab_img[i][j] = darken_color(game->tab_img[i][j], dist);
			j++;
		}
		i++;
	}
}

int	darken_color(int color, double weight)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * weight);
	g = (int)(((color >> 8) & 0xFF) * weight);
	b = (int)((color & 0xFF) * weight);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
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
	raycasting_bonus(game, 0);
	heart_hud(game);
	free_star(game->tab_img, GAME_HEIGHT);
	return (0);
}

int	key_hook(t_game *game)
{
	op_or_close_door(game);
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
			if (i >= cur_ray->start && i <= cur_ray->end)
			{
				handle_textures(game, cur_ray, x);
				i = cur_ray->end;
			}
			i++;
		}
		iter = iter->next;
	}
}
