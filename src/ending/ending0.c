/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:59:35 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/18 18:04:29 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_error(t_game *game, char *str)
{
	printf("%s\n", str);
	end(game);
}

void	end(t_game *game)
{
	if (game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}
