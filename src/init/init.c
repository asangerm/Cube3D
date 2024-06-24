/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:57:54 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/24 14:42:43 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_info(t_info *info)
{
	info->no_path = NULL;
	info->so_path = NULL;
	info->we_path = NULL;
	info->ea_path = NULL;
	info->c_color = NULL;
	info->f_color = NULL;
}

void	init_ray(t_ray *ray)
{
	ray->cameraX = 0;
	ray->dirX = 0;
	ray->dirY = 0;
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
}

void	init(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	init_map(&game->map);
	init_player(&game->player);
}
