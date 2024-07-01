/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:24:34 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/01 23:30:18 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_img_ray(int **text, t_game *game)
{
	t_image	image;
	int		i;
	int		j;

	image.img = mlx_new_image(game->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	image.data = (int *)mlx_get_data_addr(image.img, &image.bpp,
			&image.size_line, &image.endian);
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			set_pixel(&image, i, j, text[i][j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
}

void	draw_line(t_ray *ray, t_game *game, int x)
{
	int	i;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		if (i < ray->start)
			game->text[i][x] = 0xa7d6ff;
		else if (i >= ray->start && i <= ray->end)
		{
			game->text[i][x] = 0x22427c;
			if (ray->side == 1)
				game->text[i][x] /= 2;
		}
		else
			game->text[i][x] = 0xcab2a3;
		i++;
	}
}

int	draw(t_game *game)
{
	int	i;

	game->text = malloc((WINDOW_HEIGHT + 1) * sizeof(int *));
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		game->text[i] = malloc((WINDOW_WIDTH + 1)
				* sizeof(int));
		i++;
	}
	raycasting(game);
	free_star(game->text, WINDOW_HEIGHT);
	return (0);
}
