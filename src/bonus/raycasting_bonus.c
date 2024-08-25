/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:48:45 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/24 17:52:39 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	wall_height(t_game *game, t_ray *ray, t_player *player)
{
	open_close_check(game, ray);
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
	init_textures_bonus(game, ray);
}

void	add_door_ray(t_game *game, t_ray *ray)
{
	t_list	*new;
	t_ray	*opdoor_ray;
	int		hit;

	check_door(game, ray, &hit);
	if (hit == 0)
		return ;
	opdoor_ray = malloc(sizeof(t_ray));
	opdoor_ray->cellx = ray->cellx;
	opdoor_ray->celly = ray->celly;
	opdoor_ray->side = ray->side;
	opdoor_ray->side = ray->side;
	opdoor_ray->side_x = ray->side_x;
	opdoor_ray->side_y = ray->side_y;
	opdoor_ray->map_x = ray->map_x;
	opdoor_ray->map_y = ray->map_y;
	opdoor_ray->dir_x = ray->dir_x;
	opdoor_ray->dir_y = ray->dir_y;
	opdoor_ray->delta_x = ray->delta_x;
	opdoor_ray->step_x = ray->step_x;
	opdoor_ray->delta_y = ray->delta_y;
	opdoor_ray->step_y = ray->step_y;
	wall_height(game, opdoor_ray, &game->player);
	new = ft_lstnew((void *)opdoor_ray);
	ft_lstadd_front(&game->lst_ray, new);
}

int	darken_color(int color, double weight)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * weight);
	g = (int)(((color >> 8) & 0xFF) * weight);
	b = (int)((color & 0xFF) * weight);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

void	open_close_check(t_game *game, t_ray *ray)
{
	if (ft_strchr("CO", game->map.real_map[ray->map_y][ray->map_x]))
	{
		if (ray->side == 0)
			ray->dist_w = (ray->side_x - ray->delta_x / 2);
		else
			ray->dist_w = (ray->side_y - ray->delta_y / 2);
	}
	else
	{
		if (ray->side == 0)
			ray->dist_w = (ray->side_x - ray->delta_x);
		else
			ray->dist_w = (ray->side_y - ray->delta_y);
	}
}

void	dda_bonus(t_game *game, t_ray *ray)
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
		if (strchr("O", game->map.real_map[ray->map_y][ray->map_x]))
			add_door_ray(game, ray);
		else if (strchr("1", game->map.real_map[ray->map_y][ray->map_x]))
			hit = 1;
		else if (strchr("C", game->map.real_map[ray->map_y][ray->map_x]))
			check_door(game, ray, &hit);
	}
}

void	raycasting_bonus(t_game *game, int x)
{
	t_player	*player;
	t_list		*new;
	t_ray		*ray;

	floor_ceiling(game);
	player = &(game->player);
	player_start(player);
	x = 0;
	while (x < GAME_WIDTH)
	{
		game->lst_ray = NULL;
		ray = init_raycasting(x, player);
		init_dda(ray, player);
		dda_bonus(game, ray);
		wall_height(game, ray, player);
		new = ft_lstnew((void *)ray);
		ft_lstadd_front(&game->lst_ray, new);
		draw_line(game, x);
		ft_lstclear(&game->lst_ray, free);
		x++;
	}
	dark_circle(game);
	print_img_ray(game->tab_img, game);
	draw_map(game, 0, 0);
	calculate_and_display_fps(game);
}