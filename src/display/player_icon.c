/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_icon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:42:09 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/08 17:42:47 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_triangle_north(t_game *game, int x, int y, int colorp)
{
	int	i;
	int	j;
	int	size;
	int	step;

	i = 0;
	size = game->tile_size;
	step = size / 2 - 1;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (j < size / 2 && j - step >= 0)
				game->mini_map[x * size + i + 2][y * size + j + 2] = colorp;
			if (j >= size / 2 && j + step <= size - 1)
				game->mini_map[x * size + i + 2][y * size + j + 2] = colorp;
			j++;
		}
		if (i % 2 == 1)
			step --;
		i++;
	}
}

void	draw_triangle_south(t_game *game, int x, int y, int colorp)
{
	int	i;
	int	j;
	int	size;
	int	step;

	i = 0;
	step = 0;
	size = game->tile_size;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (j < size / 2 && j >= step)
				game->mini_map[x * size + i + 2][y * size + j + 2] = colorp;
			if (j >= size / 2 && j <= size - 1 - step)
				game->mini_map[x * size + i + 2][y * size + j + 2] = colorp;
			j++;
		}
		if (i % 2 == 1)
			step++;
		i++;
	}
}

void	draw_triangle_east(t_game *game, int x, int y, int colorp)
{
	int	i;
	int	j;
	int	size;
	int	step;

	i = 0;
	step = 0;
	size = game->tile_size;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i < size / 2 && (j - step <= i || j - step - 1 <= i))
				game->mini_map[x * size + i + 2][y * size + j + 2] = colorp;
			if (i >= size / 2 && (j - step <= i || j - step - 1 <= i))
				game->mini_map[x * size + i + 2][y * size + j + 2] = colorp;
			j++;
		}
		if (i < size / 2 - 1)
			step ++;
		else
			step -= 3;
		i++;
	}
}

void	draw_triangle_west(t_game *game, int x, int y, int colorp)
{
	int	i;
	int	j;
	int	size;
	int	step;

	i = 0;
	size = game->tile_size;
	step = size - 2;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i < size / 2 && j >= step)
				game->mini_map[x * size + i + 2][y * size + j + 2] = colorp;
			if (i >= size / 2 && (i - j) <= (size / 2) - step)
				game->mini_map[x * size + i + 2][y * size + j + 2] = colorp;
			j++;
		}
		if (i < size / 2 - 1)
			step -= 2;
		else
			step += 1;
		i++;
	}
}

void	draw_player(t_game *game, int x, int y, int colorp)
{
	x = x - (int)game->player.y + 3;
	y = y - (int)game->player.x + 3;
	if (game->player.dir_x >= sqrt(2) / 2)
		draw_triangle_east(game, x, y, colorp);
	if (game->player.dir_x <= -sqrt(2) / 2)
		draw_triangle_west(game, x, y, colorp);
	if (game->player.dir_y < -sqrt(2) / 2)
		draw_triangle_north(game, x, y, colorp);
	if (game->player.dir_y > sqrt(2) / 2)
		draw_triangle_south(game, x, y, colorp);
}
