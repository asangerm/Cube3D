/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_endinit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:57:54 by asangerm          #+#    #+#             */
/*   Updated: 2024/08/25 19:11:18 by nfradet          ###   ########.fr       */
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

void	init_player(t_player *player)
{
	player->face_to = '0';
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->rota = 0;
	player->move_x = 0;
	player->move_y = 0;
}

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
