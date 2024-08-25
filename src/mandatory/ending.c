/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:59:35 by asangerm          #+#    #+#             */
/*   Updated: 2024/08/25 18:56:32 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_info(t_info *info)
{
	if (info->no_path)
		free(info->no_path);
	if (info->so_path)
		free(info->so_path);
	if (info->we_path)
		free(info->we_path);
	if (info->ea_path)
		free(info->ea_path);
	if (info->c_color)
		free(info->c_color);
	if (info->f_color)
		free(info->f_color);
}

void	free_texture(t_game *game, t_textures *text)
{
	if (text->ea.img)
		mlx_destroy_image(game->mlx, text->ea.img);
	if (text->we.img)
		mlx_destroy_image(game->mlx, text->we.img);
	if (text->so.img)
		mlx_destroy_image(game->mlx, text->so.img);
	if (text->no.img)
		mlx_destroy_image(game->mlx, text->no.img);
}

void	free_map(t_map *map)
{
	free_tab(map->split_path);
	free_tab(map->tab);
	free_tab(map->real_map);
	free_info(&map->map_info);
}

void	end(t_game *game)
{
	free_texture(game, &game->textures);
	if (game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(&game->map);
	exit(0);
}
