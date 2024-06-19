/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:36:02 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/19 04:36:16 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	*color_convert(t_game *game, char **colors, int *c)
{
	int		i;

	i = 0;
	while (colors[i])
	{
		c[i] = ft_atoi(colors[i]);
		if (c[i] < 0 || no_digit(colors[i]) == 1)
		{
			free_tab(colors);
			free(c);
			ft_error(game, INVALID_COLOR);
		}
		i++;
	}
	free_tab(colors);
	return (c);
}

int	*set_color(t_game *game, char *line)
{
	char	**colors;
	int		*c;
	int		i;

	colors = ft_split(line, ',');
	i = 0;
	while (colors[i])
		i++;
	if (i != 3)
	{
		free_tab(colors);
		ft_error(game, INVALID_COLOR);
	}
	c = malloc(sizeof(int) * 3);
	if (!c)
	{
		free_tab(colors);
		ft_error(game, INVALID_COLOR);
	}
	return (color_convert(game, colors, c));
}

void	get_color(t_game *game, t_info *info, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]))
		ft_error(game, INVALID_COLOR);
	if (!info->c_color && line[j] == 'C')
		info->c_color = set_color(game, line + j + 1);
	else if (!info->f_color && line[j] == 'F')
		info->f_color = set_color(game, line + j + 1);
	else
		ft_error(game, INVALID_COLOR);
}
