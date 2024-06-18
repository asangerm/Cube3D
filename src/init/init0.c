/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:57:54 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/18 22:15:10 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_map(t_map *map)
{
	map->split_path = NULL;
}

void	init(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	init_map(&game->map);
}
