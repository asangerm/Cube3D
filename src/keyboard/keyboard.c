/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:49:50 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/24 23:04:11 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move(t_game *game, int keybind)
{
	if (keybind == K_UP)
		game->player.y -= 1;
	if (keybind == K_DOWN)
		game->player.y += 1;
	if (keybind == K_LEFT)
		game->player.x -= 1;
	if (keybind == K_RIGHT)
		game->player.x += 1;
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
	if (keybind == K_UP)
		move(game, K_UP);
	if (keybind == K_DOWN)
		move(game, K_DOWN);
	if (keybind == K_LEFT)
		move(game, K_LEFT);
	if (keybind == K_RIGHT)
		move(game, K_RIGHT);
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
