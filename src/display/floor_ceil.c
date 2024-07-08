/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:52:09 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/08 17:52:47 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_floor_ceiling_texture(t_game *game, t_ray *ray)
{
	ray->cimage = game->textures.ceiling;
	ray->fimage = game->textures.floor;
}

void	print_floor_ceiling(t_game *game, t_ray *ray, int y)
{
	int	x;

	x = 0;
	init_floor_ceiling_texture(game, ray);
	while (x < GAME_WIDTH)
	{
		ray->cellx = (int)ray->f_x;
		ray->celly = (int)ray->f_y;
		ray->t_x = (int)(ray->cimage.width * (ray->f_x - ray->cellx))
			& (ray->cimage.width - 1);
		ray->t_y = (int)(ray->cimage.height * (ray->f_y - ray->celly))
			& (ray->cimage.height - 1);
		ray->f_x += ray->f_step_x;
		ray->f_y += ray->f_step_y;
		game->tab_img[y][x]
			= ray->fimage.data[ray->cimage.width * ray->t_y + ray->t_x];
		game->tab_img[GAME_HEIGHT - y - 1][x]
			= ray->cimage.data[ray->cimage.width * ray->t_y + ray->t_x];
		x++;
	}
}

void	init_floor_ceiling(int y, t_ray *ray, t_player *player)
{
	ray->dir_x0 = player->dir_x - player->plane_x;
	ray->dir_y0 = player->dir_y - player->plane_y;
	ray->dir_x1 = player->dir_x + player->plane_x;
	ray->dir_y1 = player->dir_y + player->plane_y;
	ray->p = y - GAME_HEIGHT / 2;
	ray->posz = GAME_HEIGHT / 2;
	ray->row_dist = ray->posz / ray->p;
	ray->f_step_x = ray->row_dist * (ray->dir_x1 - ray->dir_x0) / GAME_WIDTH;
	ray->f_step_y = ray->row_dist * (ray->dir_y1 - ray->dir_y0) / GAME_WIDTH;
	ray->f_x = player->x + ray->row_dist * ray->dir_x0;
	ray->f_y = player->y + ray->row_dist * ray->dir_y0;
}

void	floor_ceiling(t_game *game)
{
	t_player	*player;
	t_ray		ray;
	int			y;

	player = &(game->player);
	player_start(player);
	y = GAME_HEIGHT / 2 + 1;
	while (y < GAME_HEIGHT)
	{
		init_floor_ceiling(y, &ray, player);
		print_floor_ceiling(game, &ray, y);
		y++;
	}
}
