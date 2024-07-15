/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:08:46 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/15 03:24:53 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_sign(double nb)
{
	if (nb < 0)
		return (-1);
	return (1);
}

void	free_star(int **tab, int h)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (i < h)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	set_pixel(t_image *image, int y, int x, int color)
{
	int	p;

	p = y * (image->size_line / 4) + x;
	image->data[p] = color;
}

void	handle_textures(t_game *game, t_ray *ray, int x)
{
	int		y;
	double	tex_pos;
	int		tex_y;
	int		color;

	tex_pos = 0;
	tex_pos = (ray->start - GAME_HEIGHT / 2 + ray->height / 2) * ray->step;
	y = ray->start;
	while (y <= ray->end)
	{
		tex_y = (int)tex_pos & (ray->image.height - 1);
		tex_pos += ray->step;
		color = ray->image.data[ray->image.height * tex_y + ray->tex_x];
		if (color >= 0)
			game->tab_img[y][x] = color;
		y++;
	}
}

void	dark_circle(t_game *game)
{
	int		i;
	int		j;
	double	dist;
	double	max_dist;

	i = 0;
	max_dist = sqrt(power(0 - GAME_WIDTH / 2) + power(0 - GAME_HEIGHT / 2));
	while (i < GAME_HEIGHT)
	{
		j = 0;
		while (j < GAME_WIDTH)
		{
			dist = sqrt(power(j - GAME_WIDTH / 2) + power(i - GAME_HEIGHT / 2));
			dist = 0.00 + (1.0 - 0.00) * power(1 - (dist / max_dist));
			game->tab_img[i][j] = darken_color(game->tab_img[i][j], dist);
			j++;
		}
		i++;
	}
}
