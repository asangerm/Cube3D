/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:49:50 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/26 16:00:52 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move2(t_game *game)
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
}

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
	draw(game);
}

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

int	key_hook(int keybind, t_game *game)
{
	move(game);
	if (keybind == K_RIGHT_ARROW)
		rotate(game, K_RIGHT_ARROW);
	if (keybind == K_LEFT_ARROW)
		rotate(game, K_LEFT_ARROW);
	if (keybind == K_ECHAP)
		end(game);
	return (0);
}

int	close_window(t_game *game)
{
	end(game);
	return (0);
}
