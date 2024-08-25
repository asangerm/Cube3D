/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:31:37 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/24 18:00:00 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_info_bonus(t_info *info)
{
	info->no_path = NULL;
	info->so_path = NULL;
	info->we_path = NULL;
	info->ea_path = NULL;
	info->cd_path = NULL;
	info->od_path = NULL;
	info->ce_path = NULL;
	info->fl_path = NULL;
	info->c_color = NULL;
	info->f_color = NULL;
}

void	init_bonus(t_game *game)
{
	game->current_time = 0.0;
	game->fps = 0;
	game->frame_count = 0;
	game->current_time = 0.0;
	game->ms_rota = 0.03;
	game->is_rota_stopping = 1;
	game->lst_ray = NULL;
	game->mlx = NULL;
	game->win = NULL;
	init_map_bonus(&game->map);
	init_player(&game->player);
	init_textures_game(&game->textures.so);
	init_textures_game(&game->textures.no);
	init_textures_game(&game->textures.ea);
	init_textures_game(&game->textures.we);
	init_textures_game(&game->textures.cd);
	init_textures_game(&game->textures.od);
	init_textures_game(&game->textures.ceiling);
	init_textures_game(&game->textures.floor);
}



void	check_center_bonus(t_game *game, char **map, int i, int j)
{
	if (!map[i - 1][j] || ft_strchr("NSEW10CO", map[i - 1][j]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i + 1][j] || ft_strchr("NSEW10CO", map[i + 1][j]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i][j - 1] || ft_strchr("NSEW10CO", map[i][j - 1]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i][j + 1] || ft_strchr("NSEW10CO", map[i][j + 1]) == NULL)
		ft_error(game, INVALID_MAP);
}

void	check_middle_bonus(t_game *game, int i, int j)
{
	char	**map;

	map = game->map.real_map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW0CO", map[i][j]) != NULL)
			{
				if (i == 0 || i == game->map.height - 1 || j == 0
					|| j == (int)ft_strlen(map[i]) - 1)
					check_border(game, game->map.real_map, i, j);
				else
					check_center_bonus(game, game->map.real_map, i, j);
			}
			j++;
		}
		i++;
	}
}

void	check_char_bonus(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\r'
			|| map[i][j] == '\v' || map[i][j] == '\f')
				j++;
			if (map[i][j])
			{
				if (!(ft_strchr("10NSEWCO", map[i][j])))
					ft_error(game, INVALID_MAP);
				if (ft_strchr("NSEW", map[i][j]) && game->player.face_to != '0')
					ft_error(game, INVALID_MAP);
				if (ft_strchr("NSEW", map[i][j]) && game->player.face_to == '0')
					game->player.face_to = map[i][j];
				j++;
			}
		}
		i++;
	}
}

void	map_checker_bonus(t_game *game)
{
	if (!game->map.real_map)
		ft_error(game, INVALID_MAP);
	if (game->map.height < 3)
		ft_error(game, INVALID_MAP);
	check_char_bonus(game, game->map.real_map);
	check_player(game, game->map.real_map);
	check_end(game);
	check_middle_bonus(game, 0, 0);
}


void	parsing_bonus(t_game *game, int argc, char **argv)
{
	arg_checker(game, argc, argv);
	map_extractor(game);
	get_data(game);
	texture_checker_bonus(game);
	color_checker(game);
	map_checker_bonus(game);
	check_doors(game);
}
