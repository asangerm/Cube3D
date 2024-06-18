/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:28:22 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/18 04:12:39 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/src/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

# define WINDOW_NAME "Cube 3D"

# define K_UP 119
# define K_DOWN 115
# define K_LEFT 97
# define K_RIGHT 100
# define K_ECHAP 65307

typedef struct s_game
{
	void	*mlx;
	void	*win;
}		t_game;

/* ending0.c */
void	end(t_game *game);

/* keyboard0.c */
int		close_window(t_game *game);

/* parsing0.c */
void	tester(void);

/* main.c */
int		main(void);

#endif