/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:30:03 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/08 22:45:17 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_side_ray(t_ray *ray)
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
}

void	dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		init_side_ray(ray);
		if (ray->map_y < 0.25
			|| ray->map_y < 0.25
			|| ray->map_y > game->map.height - 0.25
			|| ray->map_x > game->map.width - 1.25)
			break ;
		if (game->map.real_map[ray->map_y][ray->map_x] == 'O')
			add_door_ray(game, ray);
		else if (strchr("1C", game->map.real_map[ray->map_y][ray->map_x]))
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
	t_list		*new;
	t_ray		*ray;
	int			x;

	ray = malloc(sizeof(t_ray));
	floor_ceiling(game);
	player = &(game->player);
	player_start(player);
	x = 0;
	while (x < GAME_WIDTH)
	{
		game->lst_ray = NULL;
		init_raycasting(x, ray, player);
		init_dda(ray, player);
		dda(game, ray);
		wall_height(game, ray, player);
		new = ft_lstnew((void *)ray);
		ft_lstadd_front(&game->lst_ray, new);
		draw_line(game, x);
		x++;
	}
	print_img_ray(game->tab_img, game);
	draw_map(game, 0, 0);
	calculate_and_display_fps(game);
}
