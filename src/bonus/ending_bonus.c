/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:51:45 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/24 18:16:10 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_texture_bonus(t_game *game, t_textures *text)
{
	if (text->ea.img)
		mlx_destroy_image(game->mlx, text->ea.img);
	if (text->we.img)
		mlx_destroy_image(game->mlx, text->we.img);
	if (text->so.img)
		mlx_destroy_image(game->mlx, text->so.img);
	if (text->no.img)
		mlx_destroy_image(game->mlx, text->no.img);
	if (text->cd.img)
		mlx_destroy_image(game->mlx, text->cd.img);
	if (text->od.img)
		mlx_destroy_image(game->mlx, text->od.img);
	if (text->ceiling.img)
		mlx_destroy_image(game->mlx, text->ceiling.img);
	if (text->floor.img)
		mlx_destroy_image(game->mlx, text->floor.img);
}

void	free_info_bonus(t_info *info)
{
	if (info->no_path)
		free(info->no_path);
	if (info->so_path)
		free(info->so_path);
	if (info->we_path)
		free(info->we_path);
	if (info->cd_path)
		free(info->cd_path);
	if (info->od_path)
		free(info->od_path);
	if (info->ea_path)
		free(info->ea_path);
	if (info->ce_path)
		free(info->ce_path);
	if (info->fl_path)
		free(info->fl_path);
	if (info->c_color)
		free(info->c_color);
	if (info->f_color)
		free(info->f_color);
}

void	free_map_bonus(t_map *map)
{
	free_tab(map->split_path);
	free_tab(map->tab);
	free_tab(map->real_map);
	free_info_bonus(&map->map_info);
}

void	end(t_game *game)
{
	free_texture_bonus(game, &game->textures);
	if (game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map_bonus(&game->map);
	exit(0);
}
