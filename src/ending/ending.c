/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:59:35 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/10 10:18:10 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_error(t_game *game, char *str)
{
	printf("%s%s %s %s%s\n", RED, ERROR_EMOJI, ERROR_, ERROR_EMOJI, RESET);
	printf("%s%s%s\n", YELLOW, str, RESET);
	end(game);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_info(t_info *info)
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
