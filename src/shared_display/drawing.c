/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:24:34 by asangerm          #+#    #+#             */
/*   Updated: 2024/08/25 00:35:54 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_img_ray(int **tab_img, t_game *game)
{
	t_image	image;
	int		i;
	int		j;

	image.img = mlx_new_image(game->mlx, GAME_WIDTH,
			GAME_HEIGHT);
	image.data = (int *)mlx_get_data_addr(image.img, &image.bpp,
			&image.size_line, &image.endian);
	i = 0;
	while (i < GAME_HEIGHT)
	{
		j = 0;
		while (j < GAME_WIDTH)
		{
			set_pixel(&image, i, j, tab_img[i][j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
}

int	color_change(int *color)
{
	long	res;
	int		r;
	int		g;
	int		b;

	r = color[0];
	g = color[1];
	b = color[2];
	res = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (res);
}

void	draw_line(t_game *game, int x)
{
	int		i;
	t_list	*iter;
	t_ray	*cur_ray;

	iter = game->lst_ray;
	while (iter != NULL)
	{
		i = 0;
		cur_ray = (t_ray *)iter->content;
		while (i < GAME_HEIGHT)
		{
			if (i >= 0 && i < cur_ray->start)
				game->tab_img[i][x] = color_change(game->map.map_info.c_color);
			else if (i >= cur_ray->start && i <= cur_ray->end)
			{
				handle_textures(game, cur_ray, x);
				i = cur_ray->end;
			}
			else if (i > cur_ray->end && i < GAME_HEIGHT)
				game->tab_img[i][x] = color_change(game->map.map_info.f_color);
			i++;
		}
		iter = iter->next;
	}
}
