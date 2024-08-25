/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:28:24 by asangerm          #+#    #+#             */
/*   Updated: 2024/08/25 19:03:02 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_textures_bonus(t_game *game, t_ray *ray)
{
	if (game->map.real_map[ray->map_y][ray->map_x] == 'C')
		ray->image = game->textures.cd;
	if (game->map.real_map[ray->map_y][ray->map_x] == 'O')
		ray->image = game->textures.od;
	if (game->map.real_map[ray->map_y][ray->map_x] == '1')
	{
		if (ray->side == 0)
		{
			if (ray->dir_x <= 0)
				ray->image = game->textures.ea;
			else
				ray->image = game->textures.we;
		}
		else
		{
			if (ray->dir_y <= 0)
				ray->image = game->textures.so;
			else
				ray->image = game->textures.no;
		}
	}
	ray->tex_x = (int)(ray->wall_x * (double)ray->image.width);
	ray->step = 1.0 * ray->image.height / ray->height;
}

void	init_info_bonus(t_info *info)
{
	info->no_path = NULL;
	info->so_path = NULL;
	info->we_path = NULL;
	info->ea_path = NULL;
	info->cd_path = NULL;
	info->od_path = NULL;
	info->ce_path = NULL;
	info->fl_path = NULL;
	info->c_color = NULL;
	info->f_color = NULL;
}

void	init_bonus(t_game *game)
{
	game->current_time = 0.0;
	game->fps = 0;
	game->frame_count = 0;
	game->current_time = 0.0;
	game->ms_rota = 0.03;
	game->is_rota_stopping = 1;
	game->lst_ray = NULL;
	game->mlx = NULL;
	game->win = NULL;
	init_map_bonus(&game->map);
	init_player(&game->player);
	init_textures_game(&game->textures.so);
	init_textures_game(&game->textures.no);
	init_textures_game(&game->textures.ea);
	init_textures_game(&game->textures.we);
	init_textures_game(&game->textures.cd);
	init_textures_game(&game->textures.od);
	init_textures_game(&game->textures.ceiling);
	init_textures_game(&game->textures.floor);
}

void	init_map_bonus(t_map *map)
{
	map->split_path = NULL;
	map->fd = -1;
	map->height = 0;
	map->path = NULL;
	map->tab = NULL;
	map->real_map = NULL;
	map->width = 0;
	map->end_map = 0;
	init_info_bonus(&map->map_info);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_bonus(&game);
	parsing_bonus(&game, argc, argv);
	game.mlx = mlx_init();
	game.previous_time = get_time_in_seconds();
	if (!game.mlx)
		return (0);
	game.win = mlx_new_window(game.mlx, GAME_WIDTH, GAME_HEIGHT + MINIMAP_SIZE
			* TILE_SIZE + 2 * BORDER_SIZE, WINDOW_NAME);
	if (!game.win)
		return (0);
	create_mlx_textures_bonus(&game);
	draw(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_loop_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
