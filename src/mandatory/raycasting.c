/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:30:03 by asangerm          #+#    #+#             */
/*   Updated: 2024/08/24 00:51:49 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	wall_height(t_game *game, t_ray *ray, t_player *player)
{
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
		else if (strchr("1", game->map.real_map[ray->map_y][ray->map_x]))
			hit = 1;
	}
}

void	raycasting(t_game *game, int x)
{
	t_player	*player;
	t_list		*new;
	t_ray		*ray;

	player = &(game->player);
	player_start(player);
	x = 0;
	while (x < GAME_WIDTH)
	{
		game->lst_ray = NULL;
		ray = init_raycasting(x, player);
		init_dda(ray, player);
		dda(game, ray);
		wall_height(game, ray, player);
		new = ft_lstnew((void *)ray);
		ft_lstadd_front(&game->lst_ray, new);
		draw_line(game, x);
		ft_lstclear(&game->lst_ray, free);
		x++;
	}
	print_img_ray(game->tab_img, game);
}
