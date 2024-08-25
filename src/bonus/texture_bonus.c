/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:10:23 by nfradet           #+#    #+#             */
/*   Updated: 2024/08/24 18:10:55 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	else if (line[j] == 'C' && line[j + 1] == 'D' && !(info->cd_path))
		info->cd_path = get_path(line, j + 2);
	else if (line[j] == 'O' && line[j + 1] == 'D' && !(info->od_path))
		info->od_path = get_path(line, j + 2);
	else if (line[j] == 'C' && line[j + 1] == 'E' && !(info->ce_path))
		info->ce_path = get_path(line, j + 2);
	else if (line[j] == 'F' && line[j + 1] == 'L' && !(info->fl_path))
		info->fl_path = get_path(line, j + 2);
	else
		ft_error(game, INVALID_TEXT);
}

void	texture_checker_bonus(t_game *game)
{
	t_info	info;

	info = game->map.map_info;
	if (!info.no_path || !info.so_path || !info.ea_path
		|| !info.we_path || !info.fl_path || !info.ce_path
		|| !info.cd_path || !info.od_path)
		ft_error(game, INVALID_TEXT);
	if (!info.c_color || !info.f_color)
		ft_error(game, INVALID_COLOR);
	check_path(game, info.ea_path);
	check_path(game, info.no_path);
	check_path(game, info.so_path);
	check_path(game, info.we_path);
	check_path(game, info.ce_path);
	check_path(game, info.fl_path);
	check_path(game, info.od_path);
	check_path(game, info.cd_path);
}

void	create_suite_suite_bonus(t_game *game)
{
	game->textures.we.data = (int *)mlx_get_data_addr(game->textures.we.img,
			&game->textures.we.bpp, &game->textures.we.size_line,
			&game->textures.we.endian);
	game->textures.cd.data = (int *)mlx_get_data_addr(game->textures.cd.img,
			&game->textures.cd.bpp, &game->textures.cd.size_line,
			&game->textures.cd.endian);
	game->textures.od.data = (int *)mlx_get_data_addr(game->textures.od.img,
			&game->textures.od.bpp, &game->textures.od.size_line,
			&game->textures.od.endian);
	game->textures.floor.data
		= (int *)mlx_get_data_addr(game->textures.floor.img,
			&game->textures.floor.bpp, &game->textures.floor.size_line,
			&game->textures.floor.endian);
	game->textures.ceiling.data
		= (int *)mlx_get_data_addr(game->textures.ceiling.img,
			&game->textures.ceiling.bpp, &game->textures.ceiling.size_line,
			&game->textures.ceiling.endian);
}

void	create_suite_bonus(t_game *game)
{
	t_info	info;

	info = game->map.map_info;
	game->textures.od.img = mlx_xpm_file_to_image(game->mlx, info.od_path,
			&game->textures.od.width, &game->textures.od.height);
	if (game->textures.od.img == NULL)
		ft_error(game, LOADING_TEX);
	game->textures.floor.img = mlx_xpm_file_to_image(game->mlx, info.fl_path,
			&game->textures.floor.width, &game->textures.floor.height);
	if (game->textures.floor.img == NULL)
		ft_error(game, LOADING_TEX);
	game->textures.ceiling.img = mlx_xpm_file_to_image(game->mlx, info.ce_path,
			&game->textures.ceiling.width, &game->textures.ceiling.height);
	if (game->textures.ceiling.img == NULL)
		ft_error(game, LOADING_TEX);
	game->textures.so.data = (int *)mlx_get_data_addr(game->textures.so.img,
			&game->textures.so.bpp, &game->textures.so.size_line,
			&game->textures.so.endian);
	game->textures.no.data = (int *)mlx_get_data_addr(game->textures.no.img,
			&game->textures.no.bpp, &game->textures.no.size_line,
			&game->textures.no.endian);
	game->textures.ea.data = (int *)mlx_get_data_addr(game->textures.ea.img,
			&game->textures.ea.bpp, &game->textures.ea.size_line,
			&game->textures.ea.endian);
	create_suite_suite_bonus(game);
}

void	create_mlx_textures_bonus(t_game *game)
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
	game->textures.cd.img = mlx_xpm_file_to_image(game->mlx, info.cd_path,
			&game->textures.cd.width, &game->textures.cd.height);
	if (game->textures.cd.img == NULL)
		ft_error(game, LOADING_TEX);
	create_suite_bonus(game);
}

void	init_textures_bonus(t_game *game, t_ray *ray)
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
