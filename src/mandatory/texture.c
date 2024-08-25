/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:08:33 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/25 19:10:45 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
