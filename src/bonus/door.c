/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 03:20:00 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/16 18:28:34 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_ray	init_check(t_game *game, t_ray *ray)
{
	t_ray	fake;

	if (ray->side_x < ray->side_y)
	{
		fake.side_x = ray->side_x + ray->delta_x;
		fake.map_x = ray->map_x + ray->step_x;
		fake.map_y = ray->map_y;
		fake.side = 0;
		fake.dist_w = (fake.side_x - ray->delta_x);
		fake.wall_x = game->player.y + fake.dist_w * ray->dir_y;
		fake.wall_x -= floor(fake.wall_x);
	}
	else
	{
		fake.side_y = ray->side_y + ray->delta_y;
		fake.map_y = ray->map_y + ray->step_y;
		fake.map_x = ray->map_x;
		fake.side = 1;
		fake.dist_w = (fake.side_y - ray->delta_y);
		fake.wall_x = game->player.x + fake.dist_w * ray->dir_x;
		fake.wall_x -= floor(fake.wall_x);
	}
	return (fake);
}

void	check_x_side(t_game *game, t_ray *ray, t_ray *fake, int *hit)
{
	if (game->player.x < ray->map_x)
	{
		if (fake->wall_x <= 0.5)
			*hit = 0;
		else
			*hit = 1;
	}
	else if (game->player.x > ray->map_x)
	{
		if (fake->wall_x >= 0.5)
			*hit = 0;
		else
			*hit = 1;
	}
}

void	check_y_side(t_game *game, t_ray *ray, t_ray *fake, int *hit)
{
	if (game->player.y < ray->map_y)
	{
		if (fake->wall_x <= 0.5)
			*hit = 0;
		else
			*hit = 1;
	}
	else if (game->player.y > ray->map_y)
	{
		if (fake->wall_x >= 0.5)
			*hit = 0;
		else
			*hit = 1;
	}
}

void	check_door(t_game *game, t_ray *ray, int *hit)
{
	t_ray	fake;

	fake = init_check(game, ray);
	if (strchr("1", game->map.real_map[fake.map_y][fake.map_x]))
	{
		if (ray->side == 0)
			check_x_side(game, ray, &fake, hit);
		else
			check_y_side(game, ray, &fake, hit);
	}
	else
		*hit = 1;
}
