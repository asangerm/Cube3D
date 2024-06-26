/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:57:54 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/01 22:32:26 by asangerm         ###   ########.fr       */
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
	int	i;

	game->current_time = 0.0;
	game->fps = 0;
	game->frame_count = 0;
	game->current_time = 0.0;
	game->mlx = NULL;
	game->win = NULL;
	i = 0;
	while (i < 256)
	{
		game->keypressed[i] = 0;
		i++;
	}
	game->keyrotated[0] = 0;
	game->keyrotated[1] = 0;
	init_map(&game->map);
	init_player(&game->player);
}
