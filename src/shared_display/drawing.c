/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:24:34 by asangerm          #+#    #+#             */
/*   Updated: 2024/08/25 19:00:07 by nfradet          ###   ########.fr       */
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
