/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:41:24 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/15 02:21:10 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	x = x - (int)game->player.y + 3;
	y = y - (int)game->player.x + 3;
	size = game->tile_size;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			game->mini_map[x * size + i + 2][y * size + j + 2] = color;
			j++;
		}
		i++;
	}
}

void	print_image(int **mini_map, t_game *game, int tile_size)
{
	t_image	image;
	int		i;
	int		j;

	image.img = mlx_new_image(game->mlx, MINIMAP_SIZE * tile_size + 4,
			MINIMAP_SIZE * tile_size + 4);
	image.data = (int *)mlx_get_data_addr(image.img, &image.bpp,
			&image.size_line, &image.endian);
	i = 0;
	while (i < MINIMAP_SIZE * tile_size + 4)
	{
		j = 0;
		while (j < MINIMAP_SIZE * tile_size + 4)
		{
			set_pixel(&image, i, j, mini_map[i][j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win,
		image.img, GAME_WIDTH / 2 - MINIMAP_SIZE * tile_size / 2, GAME_HEIGHT);
	mlx_destroy_image(game->mlx, image.img);
}

void	handle_drawing(t_game *game, int i, int j)
{
	if (i >= (int)(game->player.y) - 3 && i <= (int)(game->player.y) + 3
	&& j >= (int)(game->player.x) - 3 && j <= (int)(game->player.x) + 3)
	{
		if (game->map.real_map[i][j] == '0')
			draw_square(game, i, j, 0xA9A9A9);
		else if (game->map.real_map[i][j] == '1')
			draw_square(game, i, j, 0x808080);
		else if (game->map.real_map[i][j] == 'C')
			draw_square(game, i, j, 0x643603 / 2);
		else if (game->map.real_map[i][j] == 'O')
			draw_square(game, i, j, 0x643603);
		else
			draw_square(game, i, j, 0x000000);
		if ((int)(game->player.x) == j && (int)(game->player.y) == i)
			draw_player(game, i, j, 0xDC143C);
	}
}

void	handle_outline(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SIZE * game->tile_size + 4)
	{
		j = 0;
		while (j < MINIMAP_SIZE * game->tile_size + 4)
		{
			if (i <= 2 || j <= 2 || i >= MINIMAP_SIZE * game->tile_size + 2
				|| j >= MINIMAP_SIZE * game->tile_size + 2)
				game->mini_map[i][j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game, int i, int j)
{
	int		tile_size;

	tile_size = 20;
	game->tile_size = tile_size;
	init_text(game, tile_size);
	while (game->map.real_map[i])
	{
		j = 0;
		while (game->map.real_map[i][j])
		{
			handle_drawing(game, i, j);
			j++;
		}
		i++;
	}
	handle_outline(game);
	print_image(game->mini_map, game, tile_size);
	free_star(game->mini_map, MINIMAP_SIZE * tile_size + 4);
}
