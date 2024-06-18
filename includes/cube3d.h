/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:28:22 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/18 03:33:55 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/src/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_game
{
	void	*mlx;
	void	*win;
}		t_game;

/* parsing0.c */
void	tester();

/* main.c */
int		main();

#endif