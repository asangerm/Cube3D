/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:19:43 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/24 00:34:17 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	check_middle(t_game *game, int i, int j)
{
	char	**map;

	map = game->map.real_map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW0", map[i][j]) != NULL)
			{
				if (i == 0 || i == game->map.height - 1 || j == 0
					|| j == (int)ft_strlen(map[i]) - 1)
					check_border(game, game->map.real_map, i, j);
				else
					check_center(game, game->map.real_map, i, j);
			}
			j++;
		}
		i++;
	}
}

void	check_center(t_game *game, char **map, int i, int j)
{
	if (!map[i - 1][j] || ft_strchr("NSEW10", map[i - 1][j]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i + 1][j] || ft_strchr("NSEW10", map[i + 1][j]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i][j - 1] || ft_strchr("NSEW10", map[i][j - 1]) == NULL)
		ft_error(game, INVALID_MAP);
	if (!map[i][j + 1] || ft_strchr("NSEW10", map[i][j + 1]) == NULL)
		ft_error(game, INVALID_MAP);
}

void	get_textures(t_game *game, t_info *info, char *line, int j)
{
	if (line[j + 2] && ft_isprint(line[j + 2]))
		ft_error(game, INVALID_TEXT);
	if (line[j] == 'N' && line[j + 1] == 'O' && !(info->no_path))
		info->no_path = get_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(info->so_path))
		info->so_path = get_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(info->we_path))
		info->we_path = get_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(info->ea_path))
		info->ea_path = get_path(line, j + 2);
	else
		ft_error(game, INVALID_TEXT);
}

void	data_checker(t_game *game)
{
	texture_checker(game);
	color_checker(game);
	map_checker(game);
}

void	parsing(t_game *game, int argc, char **argv)
{
	arg_checker(game, argc, argv);
	map_extractor(game);
	get_data(game);
	data_checker(game);
}

void	check_char(t_game *game, char **map)
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
				if (!(ft_strchr("10NSEW", map[i][j])))
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

void	create_suite(t_game *game)
{
	game->textures.so.data = (int *)mlx_get_data_addr(game->textures.so.img,
			&game->textures.so.bpp, &game->textures.so.size_line,
			&game->textures.so.endian);
	game->textures.no.data = (int *)mlx_get_data_addr(game->textures.no.img,
			&game->textures.no.bpp, &game->textures.no.size_line,
			&game->textures.no.endian);
	game->textures.ea.data = (int *)mlx_get_data_addr(game->textures.ea.img,
			&game->textures.ea.bpp, &game->textures.ea.size_line,
			&game->textures.ea.endian);
	game->textures.we.data = (int *)mlx_get_data_addr(game->textures.we.img,
			&game->textures.we.bpp, &game->textures.we.size_line,
			&game->textures.we.endian);
}

void	create_mlx_textures(t_game *game)
{
	t_info	info;

	info = game->map.map_info;
	game->textures.so.img = mlx_xpm_file_to_image(game->mlx, info.so_path,
			&game->textures.so.width, &game->textures.so.height);
	if (game->textures.so.img == NULL)
		ft_error(game, LOADING_TEX);
	game->textures.no.img = mlx_xpm_file_to_image(game->mlx, info.no_path,
			&game->textures.no.width, &game->textures.no.height);
	if (game->textures.no.img == NULL)
		ft_error(game, LOADING_TEX);
	game->textures.ea.img = mlx_xpm_file_to_image(game->mlx, info.ea_path,
			&game->textures.ea.width, &game->textures.ea.height);
	if (game->textures.ea.img == NULL)
		ft_error(game, LOADING_TEX);
	game->textures.we.img = mlx_xpm_file_to_image(game->mlx, info.we_path,
			&game->textures.we.width, &game->textures.we.height);
	if (game->textures.we.img == NULL)
		ft_error(game, LOADING_TEX);
	create_suite(game);
}

void	texture_checker(t_game *game)
{
	t_info	info;

	info = game->map.map_info;
	if (!info.no_path || !info.so_path || !info.ea_path
		|| !info.we_path)
		ft_error(game, INVALID_TEXT);
	if (!info.c_color || !info.f_color)
		ft_error(game, INVALID_COLOR);
	check_path(game, info.ea_path);
	check_path(game, info.no_path);
	check_path(game, info.so_path);
	check_path(game, info.we_path);
}

void	map_checker(t_game *game)
{
	if (!game->map.real_map)
		ft_error(game, INVALID_MAP);
	if (game->map.height < 3)
		ft_error(game, INVALID_MAP);
	check_char(game, game->map.real_map);
	check_player(game, game->map.real_map);
	check_end(game);
	check_middle(game, 0, 0);
}
