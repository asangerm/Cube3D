/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:38:47 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/21 02:07:11 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_square(t_game *game, int x, int y, int len, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int		tile_size;
	int		begin_x;
	int		begin_y;
	int		i;
	int		j;
	int		x;
	int		y;
	char	**map;

	tile_size = 20;
	map = game->map.real_map;
	begin_x = 5;
	begin_y = 5;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			x = begin_x + j * tile_size;
			y = begin_y + i * tile_size;
			if (map[i][j] == '0')
				draw_square(game, x, y, tile_size, 0xA9A9A9);
			else if (map[i][j] == '1')
				draw_square(game, x, y, tile_size, 0x808080);
			else if (ft_strchr("NSWE", map[i][j]) != NULL)
				draw_square(game, x, y, tile_size, 0xDC143C);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	init(&game);
	parsing(&game, argc, argv);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (0);
	game.win = mlx_new_window(game.mlx, 20 * 64,
			15 * 64, WINDOW_NAME);
	if (!game.win)
		return (0);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	draw_map(&game);
	mlx_loop(game.mlx);
	return (0);
}
