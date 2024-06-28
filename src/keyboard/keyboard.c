/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:49:50 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/28 13:52:26 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*void	move2(t_game *game)
{
	if (game->player.face_to == 'E')
	{
		if (game->keypressed[K_UP] == 1)
			game->player.x += 0.1;
		if (game->keypressed[K_DOWN] == 1)
			game->player.x -= 0.1;
		if (game->keypressed[K_LEFT] == 1)
			game->player.y -= 0.1;
		if (game->keypressed[K_RIGHT] == 1)
			game->player.y += 0.1;
	}
	else if (game->player.face_to == 'W')
	{
		if (game->keypressed[K_UP] == 1)
			game->player.x -= 0.1;
		if (game->keypressed[K_DOWN] == 1)
			game->player.x += 0.1;
		if (game->keypressed[K_LEFT] == 1)
			game->player.y += 0.1;
		if (game->keypressed[K_RIGHT] == 1)
			game->player.y -= 0.1;
	}
}*/
/*
void	move(t_game *game)
{
	if (game->player.face_to == 'N')
	{
		if (game->keypressed[K_UP] == 1)
			game->player.y -= 0.1;
		if (game->keypressed[K_DOWN] == 1)
			game->player.y += 0.1;
		if (game->keypressed[K_LEFT] == 1)
			game->player.x -= 0.1;
		if (game->keypressed[K_RIGHT] == 1)
			game->player.x += 0.1;
	}
	else if (game->player.face_to == 'S')
	{
		if (game->keypressed[K_UP] == 1)
			game->player.y += 0.1;
		if (game->keypressed[K_DOWN] == 1)
			game->player.y -= 0.1;
		if (game->keypressed[K_LEFT] == 1)
			game->player.x += 0.1;
		if (game->keypressed[K_RIGHT] == 1)
			game->player.x -= 0.1;
	}
	else
		move2(game);
}*/

void	move(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x;
	next_y = game->player.y;
	printf("playerX %f\n", game->player.x);
	printf("playerY %f\n", game->player.y);
	if (game->keypressed[K_UP] == 1)
	{
		next_x = game->player.x + game->player.dirX * 0.1;
		next_y = game->player.y + game->player.dirY * 0.1;
	}
	if (game->keypressed[K_DOWN] == 1)
	{
		next_x = game->player.x - game->player.dirX * 0.1;
		next_y = game->player.y - game->player.dirY * 0.1;
	}
	if (game->keypressed[K_LEFT] == 1)
	{
		next_x = game->player.x + game->player.dirY * 0.1;
		next_y = game->player.y - game->player.dirX * 0.1;
	}
	if (game->keypressed[K_RIGHT] == 1)
	{
		next_x = game->player.x - game->player.dirY * 0.1;
		next_y = game->player.y + game->player.dirX * 0.1;
	}
	ft_printf("map next %c\n", game->map.real_map[(int)next_y][(int)game->player.x]);
	printf("nextX %f\n", next_x);
	printf("nexty %f\n", next_y);
	if (game->map.real_map[(int)next_y][(int)game->player.x] != '1')
		game->player.y = next_y;
	if (game->map.real_map[(int)game->player.y][(int)next_x] != '1')
		game->player.x = next_x;
	ft_printf("---------------------------------------------------------\n");
}

// void	move(t_game *game)
// {
// 	if (game->keypressed[K_UP] == 1)
// 	{
// 		game->player.x += game->player.dirX * 0.1;
// 		game->player.y += game->player.dirY * 0.1;
// 	}
// 	if (game->keypressed[K_DOWN] == 1)
// 	{
// 		game->player.x -= game->player.dirX * 0.1;
// 		game->player.y -= game->player.dirY * 0.1;
// 	}
// 	if (game->keypressed[K_LEFT] == 1)
// 	{
// 		game->player.x += game->player.dirY * 0.1;
// 		game->player.y -= game->player.dirX * 0.1;
// 	}
// 	if (game->keypressed[K_RIGHT] == 1)
// 	{
// 		game->player.x -= game->player.dirY * 0.1;
// 		game->player.y += game->player.dirX * 0.1;
// 	}
// }

int		get_index(char *str, char c, int len)
{
	int	i;

	i = 0;
	while(i < len)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/*
void	rotate(t_game *game, int keybind)
{
	char	str[5];
	int		i;

	str[0] = 'N';
    str[1] = 'E';
    str[2] = 'S';
    str[3] = 'W';
	printf("facing avant : %c\n", game->player.face_to);
	i = get_index(str, game->player.face_to, 4);
	printf("i avant: %d\n", i);
	if (keybind == K_RIGHT_ARROW)
		i = (i + 1)%4;
	if (keybind == K_LEFT_ARROW)
	{
		if (i == 0)
			i = 3;
		else
			i -= 1;
	}
	printf("%d\n", i);
	printf("%c\n", str[i]);
	game->player.face_to = str[i];
	player_init(&(game->player));
	draw(game);
}
*/

void	rotate(t_game *game)
{
	double		rot;
	double		tmp;
	t_player	*p;

	if (game->keyrotated[0] == 1 && game->keyrotated[1] == 1)
		return ;
	if (game->keyrotated[0] == 1)
		rot = -0.1;
	else if (game->keyrotated[1] == 1)
		rot = 0.1;
	else
		return ;
	p = &(game->player);
	// printf("dirX = %f, dirY = %f\n", game->player.dirX, game->player.dirY);
	tmp = p->dirX;
	p->dirX = p->dirX * cos(rot) - p->dirY * sin(rot);
	p->dirY = tmp * sin(rot) + p->dirY * cos(rot);
	tmp = p->planeX;
	p->planeX = p->planeX * cos(rot) - p->planeY * sin(rot);
	p->planeY = tmp * sin(rot) + p->planeY * cos(rot);
	// printf("dirX = %f, dirY = %f\n", p->dirX, p->dirY);
}

int	key_hook(int keybind, t_game *game)
{
	move(game);
	rotate(game);
	draw(game);
	if (keybind == K_ECHAP)
		end(game);
	return (0);
}

int	close_window(t_game *game)
{
	end(game);
	return (0);
}
