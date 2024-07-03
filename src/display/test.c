/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:11:14 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/03 19:22:37 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = game->tile_size;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			game->mini_map[x * size + i][y * size + j] = color;
			j++;
		}
		i++;
	}
}

void	init_text(t_game *game, t_map map, int tile_size)
{
	int	i;
	int	j;

	game->mini_map = malloc((map.height * tile_size + 1) * sizeof(game->mini_map));
	i = 0;
	while (i < map.height * tile_size)
	{
		game->mini_map[i] = malloc((map.width * tile_size + 1)
				* sizeof(game->mini_map));
		i++;
	}
	i = 0;
	while (i < map.height * tile_size)
	{
		j = 0;
		while(j < map.width * tile_size)
		{
			game->mini_map[i][j] = 0x000000;
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

	image.img = mlx_new_image(game->mlx, game->map.width * tile_size,
			game->map.height * tile_size);
	image.data = (int *)mlx_get_data_addr(image.img, &image.bpp,
			&image.size_line, &image.endian);
	i = 0;
	while (i < game->map.height * tile_size)
	{
		j = 0;
		while (j < game->map.width * tile_size)
		{
			set_pixel(&image, i, j, mini_map[i][j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, image.img, WINDOW_WIDTH / 2 - game->map.width * tile_size / 2, WINDOW_HEIGHT);
	mlx_destroy_image(game->mlx, image.img);
}

void	draw_triangle_north(t_game *game, int x, int y, int colorp)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = game->tile_size;	
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (j >= size / 2 && i >= j)
				game->mini_map[x * size + i][y * size + j] = colorp;
			if (j < size / 2 && j + i >= size - 1)
				game->mini_map[x * size + i][y * size + j] = colorp;
			j++;
		}
		i++;
	}
}

void	draw_triangle_south(t_game *game, int x, int y, int colorp)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = game->tile_size;	
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (j < size / 2 && i <= j)
				game->mini_map[x * size + i][y * size + j] = colorp;
			if (j >= size / 2 && j + i <= size - 1)
				game->mini_map[x * size + i][y * size + j] = colorp;
			j++;
		}
		i++;
	}
}

void	draw_triangle_east(t_game *game, int x, int y, int colorp)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = game->tile_size;	
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i < size / 2 && i >= j)
				game->mini_map[x * size + i][y * size + j] = colorp;
			if (i >= size / 2 && j + i <= size - 1)
				game->mini_map[x * size + i][y * size + j] = colorp;
			j++;
		}
		i++;
	}
}

void	draw_triangle_west(t_game *game, int x, int y, int colorp)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = game->tile_size;	
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i >= size / 2 && i <= j)
				game->mini_map[x * size + i][y * size + j] = colorp;
			if (i < size / 2 && j + i >= size - 1)
				game->mini_map[x * size + i][y * size + j] = colorp;
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game, int x, int y, int colorp)
{
	if (game->player.dir_x >= sqrt(2) / 2)
		draw_triangle_east(game, x, y, colorp);
	if (game->player.dir_x <= -sqrt(2) / 2)
		draw_triangle_west(game, x, y, colorp);
	if (game->player.dir_y < -sqrt(2) / 2)
		draw_triangle_north(game, x, y, colorp);
	if (game->player.dir_y > sqrt(2) / 2)
		draw_triangle_south(game, x, y, colorp);
}

void	handle_drawing(t_game *game, int i, int j)
{
	if (game->map.real_map[i][j] == '0')
		draw_square(game, i, j, 0xA9A9A9);
	else if (game->map.real_map[i][j] == '1')
		draw_square(game, i, j, 0x808080);
	else
		draw_square(game, i, j, 0x000000);
	if ((int)(game->player.x) == j && (int)(game->player.y) == i)
		draw_player(game, i, j, 0xDC143C);
}

void	draw_map(t_game *game, int i, int j)
{
	int		tile_size;

	tile_size = 10;
	game->tile_size = tile_size;
	init_text(game, game->map, tile_size);
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
	print_image(game->mini_map, game, tile_size);
	free_star(game->mini_map, game->map.height * tile_size);
}
