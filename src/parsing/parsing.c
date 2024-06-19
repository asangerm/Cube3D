/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:26:49 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/19 04:41:25 by asangerm         ###   ########.fr       */
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

int	get_info(t_game *game, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1])
			&& !ft_isdigit(map[i][j + 1]))
			get_textures(game, &(game->map.map_info), map[i], j);
		else
			get_color(game, &(game->map.map_info), map[i], j);
	}
	else if (ft_isdigit(map[i][j]))
	{
		create_map(game, map, i);
		return (0);
	}
	return (1);
}

void	get_data(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.tab[i])
	{
		if (!get_info(game, game->map.tab, i, 0))
			break ;
		i++;
	}
}

void	parsing(t_game *game, int argc, char **argv)
{
	arg_checker(game, argc, argv);
	map_extractor(game);
	get_data(game);
	printf("%s\n", game->map.map_info.no_path);
	printf("%s\n", game->map.map_info.so_path);
	printf("%s\n", game->map.map_info.ea_path);
	printf("%s\n", game->map.map_info.we_path);
	print_int_star(game->map.map_info.c_color);
	print_int_star(game->map.map_info.f_color);
	print_tab(game->map.real_map);
}
