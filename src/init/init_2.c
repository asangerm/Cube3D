/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:34:42 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/08 21:03:58 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_text(t_game *game, int tile_size)
{
	int	i;
	int	j;

	game->mini_map = malloc((MINIMAP_SIZE * tile_size + 4) * sizeof(int *));
	i = 0;
	while (i < MINIMAP_SIZE * tile_size + 4)
	{
		game->mini_map[i] = malloc((MINIMAP_SIZE * tile_size + 4)
				* sizeof(int));
		i++;
	}
	i = 0;
	while (i < MINIMAP_SIZE * tile_size + 4)
	{
		j = 0;
		while (j < MINIMAP_SIZE * tile_size + 4)
		{
			game->mini_map[i][j] = 0x000000;
			j++;
		}
		i++;
	}
}

void	init_textures(t_game *game, t_ray *ray)
{
	if (game->map.real_map[ray->map_y][ray->map_x] == 'C')
		ray->image = game->textures.cd;
	if (game->map.real_map[ray->map_y][ray->map_x] == 'O')
		ray->image = game->textures.od;
	if (game->map.real_map[ray->map_y][ray->map_x] == '1')
	{
		if (ray->side == 0)
		{
			if (ray->dir_x <= 0)
				ray->image = game->textures.ea;
			else
				ray->image = game->textures.we;
		}
		else
		{
			if (ray->dir_y <= 0)
				ray->image = game->textures.so;
			else
				ray->image = game->textures.no;
		}
	}
	ray->tex_x = (int)(ray->wall_x * (double)ray->image.width);
	ray->step = 1.0 * ray->image.height / ray->height;
}

void	init_textures_game(t_image *img)
{
	img->img = NULL;
	img->height = 0;
	img->width = 0;
	img->data = NULL;
	img->bpp = 0;
	img->size_line = 0;
	img->endian = 0;
}
