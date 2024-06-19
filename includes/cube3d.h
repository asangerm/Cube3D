/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:28:22 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/19 04:40:40 by asangerm         ###   ########.fr       */
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
# define INVALID_TEXT ERROR_""YELLOW"Invalid texture in file"RESET
# define INVALID_COLOR ERROR_""YELLOW"Invalid color in file"RESET
# define INVALID_MAP ERROR_""YELLOW"Invalid map in file"RESET

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
	char	**tab;
	char	**real_map;
	t_info	map_info;
	int		width;
	int		height;
	int		end_map;
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
void	free_tab(char **tab);
void	free_map(t_map *map);
void	ft_error(t_game *game, char *str);

/* keyboard0.c */
int		close_window(t_game *game);
int		key_hook(int keybind, t_game *game);

/* parsing.c */
int		split_len(char **tab);
void	get_data(t_game *game);
void	parsing(t_game *game, int argc, char **argv);
int		get_info(t_game *game, char **map, int i, int j);
void	arg_checker(t_game *game, int argc, char **argv);

/* map.c */
void	enhance_map(t_game *game);
void	map_extractor(t_game *game);
void	get_map(t_game *game, char **map, int i);
void	create_map(t_game *game, char **map, int i);
void	set_map(t_game *game, t_map *m, char **map, int w);

/* colors.c */
int		*set_color(t_game *game, char *line);
int		*color_convert(t_game *game, char **colors, int *c);
void	get_color(t_game *game, t_info *info, char *line, int j);

/* textures.c */
char	*get_path(char *line, int j);
void	get_textures(t_game *game, t_info *info, char *line, int j);

/* parsing_utils.c */
int		no_digit(char *str);
void	print_tab(char **tab);
void	print_int_star(int *tab);
int		get_width(t_map *map, int i);
int		get_height(t_game *game, char **map, int i);

/* main.c */
int		main(int argc, char **argv);

#endif