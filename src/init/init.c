/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:57:54 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/08 04:55:10 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_info(t_info *info)
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

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
}

void	init_map(t_map *map)
{
	map->split_path = NULL;
	map->fd = -1;
	map->height = 0;
	map->path = NULL;
	map->tab = NULL;
	map->real_map = NULL;
	map->width = 0;
	map->end_map = 0;
	init_info(&map->map_info);
}

void	init_player(t_player *player)
{
	player->face_to = '0';
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->rota = 0;
	player->move_x = 0;
	player->move_y = 0;
}

void	init(t_game *game)
{
	game->current_time = 0.0;
	game->fps = 0;
	game->frame_count = 0;
	game->current_time = 0.0;
	game->ms_rota = 0.03;
	game->is_rota_stopping = 1;
	game->mlx = NULL;
	game->win = NULL;
	init_map(&game->map);
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
