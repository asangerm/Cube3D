/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:28:22 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/18 03:58:21 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/src/libft.h"
# include "../minilibx-linux/mlx.h"

# define CLOSE_BUTTON 17, 1L << 17
# define WINDOW_NAME "Cube 3D"

typedef struct s_game
{
	void	*mlx;
	void	*win;
}		t_game;

/* keyboard0.c */
int		close_window(t_game *game);

/* parsing0.c */
void	tester();

/* main.c */
int		main();
void	end(t_game *game);

#endif