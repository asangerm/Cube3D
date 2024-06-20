/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:49:50 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/18 17:28:29 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	key_hook(int keybind, t_game *game)
{
	if (keybind == K_ECHAP)
		end(game);
	return (0);
}

int	close_window(t_game *game)
{
	end(game);
	return (0);
}
