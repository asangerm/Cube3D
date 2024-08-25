/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:28:47 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/24 01:27:17 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_int_star(int *tab)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("%d ", tab[i]);
		i++;
	}
	printf("\n");
}

int	no_digit(char *str)
{
	int	i;
	int	valid;

	i = 0;
	valid = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			valid = 1;
		if (str[i + 1] == '\0' && str[i] == '\n')
		{
			if (valid == 1)
				return (0);
			else
				return (1);
		}
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

int	get_width(t_map *map, int i)
{
	int	len;

	len = ft_strlen(map->tab[i]);
	if (map->tab[i][len - 1] == '\n')
		len--;
	while (map->tab[i])
	{
		if ((int)ft_strlen(map->tab[i]) > len)
		{
			len = ft_strlen(map->tab[i]);
			if (map->tab[i][len - 1] == '\n')
				len--;
		}
		i++;
	}
	return (len);
}

int	get_height(t_game *game, char **map, int i)
{
	int	index;
	int	j;

	index = i;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\r'
		|| map[i][j] == '\v' || map[i][j] == '\f')
			j++;
		if (map[i][j] != '1')
			break ;
		i++;
	}
	game->map.end_map = i;
	return (i - index);
}
