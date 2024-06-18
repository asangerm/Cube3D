/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:26:49 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/18 22:23:56 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	split_len(char **tab)
{
	int	i;

	if (tab == NULL)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	arg_checker(t_game *game, int argc, char **argv)
{
	if (argc < 2)
		ft_error(game, TOO_FEW_ARG);
	if (argc > 2)
		ft_error(game, TOO_MUCH_ARG);
	game->map.path = argv[1];
	game->map.split_path = ft_split(game->map.path, '.');
	if (split_len(game->map.split_path) != 2)
		ft_error(game, WRONG_EXT);
	if (ft_strncmp("cub", game->map.split_path[1], 4) != 0)
		ft_error(game, WRONG_EXT);
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd == -1)
		ft_error(game, CANT_OPEN);
}

void	parsing(t_game *game, int argc, char **argv)
{
	arg_checker(game, argc, argv);
}
