/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:24:46 by nfradet           #+#    #+#             */
/*   Updated: 2024/07/08 22:40:35 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	add_door_ray(t_game *game, t_ray *ray)
{
	t_list	*new;
	t_ray	*opdoor_ray;

	opdoor_ray = malloc(sizeof(t_ray));
	opdoor_ray->image = game->textures.od;
	opdoor_ray->camera_x = ray->camera_x;
	opdoor_ray->cellx = ray->cellx;
	opdoor_ray->celly = ray->celly;
	opdoor_ray->delta_x = ray->delta_x;
	opdoor_ray->delta_y = ray->delta_y;
	opdoor_ray->side = ray->side;
	opdoor_ray->side = ray->side;
	opdoor_ray->side_x = ray->side_x;
	opdoor_ray->side_y = ray->side_y;
	opdoor_ray->map_x = ray->map_x;
	opdoor_ray->map_y = ray->map_y;
	opdoor_ray->dir_x = ray->dir_x;
	opdoor_ray->dir_y = ray->dir_y;
	opdoor_ray->step_x = ray->step_x;
	opdoor_ray->step_y = ray->step_y;
	wall_height(game, opdoor_ray, &game->player);
	new = ft_lstnew((void *)opdoor_ray);
	ft_lstadd_front(&game->lst_ray, new);
}

void	wall_height(t_game *game, t_ray *ray, t_player *player)
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
	init_textures(game, ray);
}
