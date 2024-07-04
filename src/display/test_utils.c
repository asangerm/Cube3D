/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:08:46 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/04 03:59:12 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
