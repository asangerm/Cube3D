/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:28:22 by asangerm          #+#    #+#             */
/*   Updated: 2024/06/27 15:34:06 by nfradet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H


#include <time.h>

# include "../libft/src/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

# define RED "\033[0;31m"
# define YELLOW	"\033[0;33m"
# define RESET "\033[0m"

# define ERROR_EMOJI "\U000026D4"

# define WINDOW_NAME "Cube 3D"
# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480

# define K_UP 119
# define K_DOWN 115
# define K_LEFT 97
# define K_RIGHT 100
# define K_ECHAP 65307
# define K_RIGHT_ARROW 65363
# define K_LEFT_ARROW 65361

# define ERROR_ "ERROR"
# define TOO_FEW_ARG "Too few arguments!"
# define TOO_MUCH_ARG "Too much arguments!"
# define WRONG_EXT "Extension of file is incorrect"
# define CANT_OPEN "We can't open the given file"
# define INVALID_TEXT "Invalid texture in file "
# define INVALID_COLOR "Invalid color in file"
# define INVALID_MAP "Invalid map in file"

typedef struct s_info
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			*f_color;
	int			*c_color;
}		t_info;

typedef struct s_player
{
	char		face_to;
	double			dirX;//Vecteur direction player
	double			dirY;
	double			x;//Position du player
	double			y;
	double			planeX;//Vecteur direction camera
	double			planeY;
}		t_player;

typedef struct s_ray
{
	double	cameraX;//Valeur allant de -1 à 1 pour parcourir les ray
	double	dirX;//Vecteur direction du ray
	double	dirY;
	int		mapX;//Position de la case où se trouve le ray
	int		mapY;
	double	deltaX;//Distance entre deux inter avec x
	double	deltaY;//Distance entre deux inter avec y
	int		stepX;//Pas indiquant vers où l'on vas
	int		stepY;
	double	sideX;//Distance jusqu'à la prochaine inter avec x
	double	sideY;//Distance jusqu'à la prochaine inter avec y
	int		side;//Variable qui nous dit si on a touché un mur en x ou y
	double	distW;//Distance entre le mur et le player
	int		height;//Hauteur du mur (en fonction de distW)
	int		start;//pixel de départ (sur l'axe y)
	int		end;//pixel de fin (sur l'axe y)
}		t_ray;

typedef struct s_map
{
	int			fd;
	char		*path;
	char		**split_path;
	char		**tab;
	char		**real_map;
	t_info		map_info;
	int			width;
	int			height;
	int			end_map;
}		t_map;

typedef struct s_image
{
	void	*img;
	int		height;
	int		width;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
}		t_image;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			**text;//test
	int			tile_size;//test
	t_map		map;
	t_player	player;
	int			keypressed[256];
	int			keyrotated[2];

	double  previous_time;
	double  current_time;
	int     frame_count;
	int     fps;
}		t_game;

void calculate_and_display_fps(t_game *game);
double get_time_in_seconds();


/* raycasting.c */
void	print_img_rat(int **text, t_game *game);
void	draw_line(t_ray *ray, t_game *game, int x);
void	wall_height(t_ray *ray, t_player *player);
void	dda(t_game *game, t_ray *ray);
void	init_dda(t_ray *ray, t_player *player);
void	init_raycasting(int x, t_ray *ray, t_player *player);
void	raycasting(t_game *game);
void	draw(t_game *game);

/* player.c */
void	player_init_2(t_player *player);
void	player_init(t_player *player);

/* test.c */
void	draw_map(t_game *game, int i, int j);
void	draw_square(t_game *game, int x, int y, int color);
void	init_text(t_game *game, t_map map, int tile_size);
void	print_image(int **text, t_game *game, int tile_size);

/* test_utils.c */
void	free_star(int **tab, int h);
void	set_pixel(t_image *image, int y, int x, int color);

/* init.c */
void	init(t_game *game);
void	init_map(t_map *map);
void	init_ray(t_ray *ray);
void	init_info(t_info *info);
void	init_player(t_player *player);

/* ending.c */
void	end(t_game *game);
void	free_tab(char **tab);
void	free_map(t_map *map);
void	ft_error(t_game *game, char *str);

/* keyboard.c */
int		close_window(t_game *game);
int		key_hook(int keybind, t_game *game);

/* parsing.c */
int		split_len(char **tab);
void	get_data(t_game *game);
void	parsing(t_game *game, int argc, char **argv);
int		get_info(t_game *game, char **map, int i, int j);
void	arg_checker(t_game *game, int argc, char **argv);

/* map.c */
void	map_extractor(t_game *game);
void	get_map(t_game *game, char **map, int i);
void	set_map(t_game *game, t_map *m, char **map, int w);

/* map_checker.c */
void	map_checker(t_game *game);
void	check_end(t_game *game);
void	check_char(t_game *game, char **map);
void	check_position(t_game *game, char **map);
void	check_player(t_game *game, char **map);

/* map_checker_2.c */
int		is_wspace(char c);
void	check_middle(t_game *game, int i, int j);
void	check_center(t_game *game, char **map, int i, int j);
void	check_border(t_game *game, char **map, int i, int j);

/* colors.c */
void	color_checker(t_game *game);
int		*set_color(t_game *game, char *line);
int		*color_convert(t_game *game, char **colors, int *c);
void	get_color(t_game *game, t_info *info, char *line, int j);

/* textures.c */
void	data_checker(t_game *game);
char	*get_path(char *line, int j);
void	texture_checker(t_game *game);
void	check_path(t_game *game, char *path);
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