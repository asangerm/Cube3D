/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:30:03 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/08 06:22:32 by asangerm         ###   ########.fr       */
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

void	wall_height(t_ray *ray, t_player *player)
{
	(void) player;
	if (ray->side == 0)
		ray->dist_w = (ray->side_x - ray->delta_x);
	else
		ray->dist_w = (ray->side_y - ray->delta_y);
	ray->height = (int)(GAME_HEIGHT / ray->dist_w);
	ray->start = -(ray->height) / 2 + GAME_HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->height / 2 + GAME_HEIGHT / 2;
	if (ray->end >= GAME_HEIGHT)
		ray->end = GAME_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = player->y + ray->dist_w * ray->dir_y;
	else
		ray->wall_x = player->x + ray->dist_w * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25
			|| ray->map_y < 0.25
			|| ray->map_y > game->map.height - 0.25
			|| ray->map_x > game->map.width - 1.25)
			break ;
		else if (game->map.real_map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

void	init_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (player->x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - player->x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (player->y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - player->y) * ray->delta_y;
	}
}

void	init_raycasting(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);
	ray->camera_x = 2 * x / (double)GAME_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
}

void	raycasting(t_game *game)
{
	t_player	*player;
	t_ray		ray;
	int			x;

	floor_ceiling(game);
	player = &(game->player);
	player_start(player);
	x = 0;
	while (x < GAME_WIDTH)
	{
		init_raycasting(x, &ray, player);
		init_dda(&ray, player);
		dda(game, &ray);
		wall_height(&ray, player);
		draw_line(&ray, game, x);
		x++;
	}
	print_img_ray(game->tab_img, game);
	draw_map(game, 0, 0);
	calculate_and_display_fps(game);
}
