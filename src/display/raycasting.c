/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:30:03 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/02 21:03:08 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	wall_height(t_ray *ray, t_player *player)
{
	(void) player;
	if (ray->side == 0)
		ray->dist_w = (ray->side_x - ray->delta_x);
	else
		ray->dist_w = (ray->side_y - ray->delta_y);
	ray->height = (int)(WINDOW_HEIGHT / ray->dist_w);
	ray->start = -(ray->height) / 2 + WINDOW_HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->height / 2 + WINDOW_HEIGHT / 2;
	if (ray->end >= WINDOW_HEIGHT)
		ray->end = WINDOW_HEIGHT - 1;
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
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
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

	player = &(game->player);
	player_start(player);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_raycasting(x, &ray, player);
		init_dda(&ray, player);
		dda(game, &ray);
		wall_height(&ray, player);
		draw_line(&ray, game, x);
		x++;
	}
	print_img_ray(game->text, game);
	calculate_and_display_fps(game);
}
