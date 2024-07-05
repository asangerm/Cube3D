/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:31:18 by nfradet           #+#    #+#             */
/*   Updated: 2024/07/05 19:33:32 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_textures(t_game *game, t_ray *ray)
{
	if (game->map.real_map[ray->map_y][ray->map_x] == 'C')
		ray->image = game->textures.cd;
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

void	handle_textures(t_game *game, t_ray *ray, int x)
{
	int		y;
	double	tex_pos;
	int		tex_y;

	tex_pos = 0;
	tex_pos = (ray->start - WINDOW_HEIGHT / 2 + ray->height / 2) * ray->step;
	y = ray->start;
	while (y <= ray->end)
	{
		tex_y = (int)tex_pos & (ray->image.height - 1);
		tex_pos += ray->step;
		game->tab_img[y][x] = ray->image.data[ray->image.height * tex_y + ray->tex_x];
		y++;
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

void	create_suite(t_game *game)
{
	t_info	info;

	info = game->map.map_info;
	game->textures.od.img = mlx_xpm_file_to_image(game->mlx, info.od_path,
			&game->textures.od.width, &game->textures.od.height);
	if (game->textures.od.img == NULL)
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
	game->textures.we.data = (int *)mlx_get_data_addr(game->textures.we.img,
			&game->textures.we.bpp, &game->textures.we.size_line,
			&game->textures.we.endian);
	game->textures.cd.data = (int *)mlx_get_data_addr(game->textures.cd.img,
			&game->textures.cd.bpp, &game->textures.cd.size_line,
			&game->textures.cd.endian);
	game->textures.od.data = (int *)mlx_get_data_addr(game->textures.od.img,
			&game->textures.od.bpp, &game->textures.od.size_line,
			&game->textures.od.endian);
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
	game->textures.cd.img = mlx_xpm_file_to_image(game->mlx, info.cd_path,
			&game->textures.cd.width, &game->textures.cd.height);
	if (game->textures.cd.img == NULL)
		ft_error(game, LOADING_TEX);
	create_suite(game);
}
