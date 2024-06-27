/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:30:03 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/27 15:41:24 by nfradet          ###   ########.fr       */
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

void	wall_height(t_ray *ray, t_player *player)
{
	(void) player;
	//printf("sideX = %f, sideY = %f, deltaX = %f, deltaY = %f\n", ray->sideX, ray->sideY, ray->deltaX, ray->deltaY);
	if (ray->side == 0)
		ray->distW = (ray->sideX - ray->deltaX);
	else
		ray->distW = (ray->sideY - ray->deltaY);
	//printf("distW = %f\n", ray->distW);
	ray->height = (int)(WINDOW_HEIGHT / ray->distW);
	ray->start = -(ray->height) / 2 + WINDOW_HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->height / 2 + WINDOW_HEIGHT / 2;
	if (ray->end >= WINDOW_HEIGHT)
		ray->end = WINDOW_HEIGHT - 1;
	//printf("start :%d, end = %d\n", ray->start, ray->end);
}

void	dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sideX < ray->sideY)
		{
			ray->sideX += ray->deltaX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideY += ray->deltaY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->mapY < 0.25
			|| ray->mapY < 0.25
			|| ray->mapY > game->map.height - 0.25
			|| ray->mapX > game->map.width - 1.25)
			break ;
		else if (game->map.real_map[ray->mapY][ray->mapX] > '0')
			hit = 1;
	}
}

void	init_dda(t_ray *ray, t_player *player)
{
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideX = (player->x - ray->mapX) * ray->deltaX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideX = (ray->mapX + 1.0 - player->x) * ray->deltaX;
	}
	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideY = (player->y - ray->mapY) * ray->deltaY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideY = (ray->mapY + 1.0 - player->y) * ray->deltaY;
	}
}

void	init_raycasting(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);
	ray->cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dirX = player->dirX + player->planeX * ray->cameraX;
	ray->dirY = player->dirY + player->planeY * ray->cameraX;
	ray->mapX = (int)player->x;
	ray->mapY = (int)player->y;
	ray->deltaX = fabs(1 / ray->dirX);
	ray->deltaY = fabs(1 / ray->dirY);
	/*printf("CameraX = %f, dirX = %f, dirY = %f, mapX = %d, \
		mapY = %d, deltaX = %f, deltaY = %f\n", ray->cameraX, ray->dirX, ray->dirY, ray->mapX, ray->mapY, ray->deltaX, ray->deltaY);

*/}

void	raycasting(t_game *game)
{
	t_player	*player;
	t_ray		ray;
	int			x;

	player = &(game->player);
	player_init(player);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_raycasting(x, &ray, player);
		init_dda(&ray, player);
		dda(game, &ray);
		wall_height(&ray, player);
		draw_line(&ray, game, x);
		x++;
	}
	print_img_ray(game->text, game);
	calculate_and_display_fps(game);
}

void	draw(t_game *game)
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
}
