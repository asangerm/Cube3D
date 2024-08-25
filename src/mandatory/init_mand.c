/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:24:40 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/24 17:58:32 by nfradet          ###   ########.fr       */
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

void	init(t_game *game)
{
	game->ms_rota = 0.03;
	game->is_rota_stopping = 1;
	game->lst_ray = NULL;
	game->mlx = NULL;
	game->win = NULL;
	init_map(&game->map);
	init_player(&game->player);
	init_textures_game(&game->textures.so);
	init_textures_game(&game->textures.no);
	init_textures_game(&game->textures.ea);
	init_textures_game(&game->textures.we);
}

void	init_textures(t_game *game, t_ray *ray)
{
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