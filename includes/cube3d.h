/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:28:22 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/18 22:23:35 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/src/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

# define RED "\033[0;31m"
# define YELLOW	"\033[0;33m"
# define RESET "\033[0m"

# define ERROR_EMOJI "\U000026D4"

# define WINDOW_NAME "Cube 3D"

# define K_UP 119
# define K_DOWN 115
# define K_LEFT 97
# define K_RIGHT 100
# define K_ECHAP 65307

# define ERROR_ RED""ERROR_EMOJI" ERROR "ERROR_EMOJI"\n"RESET
# define TOO_FEW_ARG ERROR_""YELLOW"Too few arguments!"RESET
# define TOO_MUCH_ARG ERROR_""YELLOW"Too much arguments!"RESET
# define WRONG_EXT ERROR_""YELLOW"Extension of file is incorrect"RESET
# define CANT_OPEN ERROR_""YELLOW"We can't open the given file"RESET

typedef struct s_info
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		*f_color;
	int		*c_color;
}		t_info;

typedef struct s_map
{
	int		fd;
	char	*path;
	char	**split_path;
	t_info	map_info;
	int		width;
	int		height;
}		t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
}		t_game;

/* init0.c */
void	init(t_game *game);
void	init_map(t_map *map);

/* ending0.c */
void	end(t_game *game);
void	free_map(t_map *map);
void	ft_error(t_game *game, char *str);

/* keyboard0.c */
int		close_window(t_game *game);
int		key_hook(int keybind, t_game *game);

/* parsing0.c */
int		split_len(char **tab);
void	parsing(t_game *game, int argc, char **argv);
void	arg_checker(t_game *game, int argc, char **argv);

/* main.c */
int		main(int argc, char **argv);

#endif