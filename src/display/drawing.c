/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 23:24:34 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/02 21:29:06 by nfradet          ###   ########.fr       */
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

void	init_textures(t_game *game, t_ray *ray)
{
	// t_image	image;
	// double		tex_width;

	if (ray->side == 0)
	{
		if (ray->dir_x <= 0) // east
			ray->image = game->textures.ea;
		else //west
			ray->image = game->textures.we;
	}
	else
	{
		if (ray->dir_y <= 0) //south
			ray->image = game->textures.so;
		else //north
			ray->image = game->textures.no;
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
		game->text[y][x] = ray->image.data[ray->image.height * tex_y + ray->tex_x];
		y++;
	}
}

void	draw_line(t_ray *ray, t_game *game, int x)
{
	int		i;

	i = 0;
	init_textures(game, ray);
	while (i < WINDOW_HEIGHT)
	{
		if (i < ray->start)
			game->text[i][x] = WOL_CEIL;
		else if (i >= ray->start && i <= ray->end)
		{
			handle_textures(game, ray, x);
			i = ray->end;
		}
		else
			game->text[i][x] = WOL_FLOOR;
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
