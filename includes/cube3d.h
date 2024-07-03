/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:28:22 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/03 15:28:41 by asangerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <time.h>
# include "../libft/src/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

# define WOL_CEIL 0x3b3b3b
# define WOL_FLOOR 0x737373
# define WOL_WALL 0x0000FF

# define RED "\033[0;31m"
# define YELLOW	"\033[0;33m"
# define RESET "\033[0m"

# define ERROR_EMOJI "\U000026D4"

# define WINDOW_NAME "Cube 3D"
# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480

# define MOVE_SPEED 0.03

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
# define LOADING_TEX "Error while loading texture"
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

typedef struct s_player
{
	char		face_to;
	double		dir_x;//Vecteur direction player
	double		dir_y;
	double		x;//Position du player
	double		y;
	double		plane_x;//Vecteur direction camera
	double		plane_y;
	int			move_x;//Direction déplacement x
	int			move_y;//Direction déplacement y
	int			rota;//Sens de rotation
}		t_player;

typedef struct s_ray
{
	double	camera_x;//Valeur allant de -1 à 1 pour parcourir les ray
	double	dir_x;//Vecteur direction du ray
	double	dir_y;
	int		map_x;//Position de la case où se trouve le ray
	int		map_y;
	double	delta_x;//Distance entre deux inter avec x
	double	delta_y;//Distance entre deux inter avec y
	int		step_x;//Pas indiquant vers où l'on vas
	int		step_y;
	double	side_x;//Distance jusqu'à la prochaine inter avec x
	double	side_y;//Distance jusqu'à la prochaine inter avec y
	int		side;//Variable qui nous dit si on a touché un mur en x ou y
	double	dist_w;//Distance entre le mur et le player
	int		height;//Hauteur du mur (en fonction de dist_w)
	int		start;//pixel de départ (sur l'axe y)
	int		end;//pixel de fin (sur l'axe y)
	double	wall_x;//la coordonnee x ou le mur a ete touche
	int		tex_x;//la coordonnee x de la texture
	double	step;
	t_image	image;
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

typedef struct s_textures
{
	t_image	so;
	t_image	no;
	t_image	we;
	t_image	ea;
}		t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			**tab_img;//test
	int			**mini_map;//test
	int			tile_size;//test
	t_map		map;
	t_player	player;
	t_textures	textures;
	int			keypressed[256];
	int			keyrotated[2];
	double		previous_time;
	double		current_time;
	int			frame_count;
	int			fps;
}		t_game;

/*-------------------- display --------------------*/

/* drawing.c */
int		draw(t_game *game);
int		color_change(int *color);
void	print_img_ray(int **text, t_game *game);
void	draw_line(t_ray *ray, t_game *game, int x);
void	free_texture(t_game *game, t_textures *text);

/* fps.c */
double	get_time_in_seconds(void);
void	calculate_and_display_fps(t_game *game);

/* raycasting.c */
void	raycasting(t_game *game);
void	dda(t_game *game, t_ray *ray);
void	init_dda(t_ray *ray, t_player *player);
void	wall_height(t_ray *ray, t_player *player);
void	init_raycasting(int x, t_ray *ray, t_player *player);

/* test_utils.c */
void	free_star(int **tab, int h);
void	set_pixel(t_image *image, int y, int x, int color);

/* test.c */
void	draw_map(t_game *game, int i, int j);
void	init_text(t_game *game, t_map map, int tile_size);
void	draw_square(t_game *game, int x, int y, int color);
void	print_image(int **text, t_game *game, int tile_size);

/*-------------------- ending --------------------*/

/* ending.c */
void	end(t_game *game);
void	free_tab(char **tab);
void	free_map(t_map *map);
void	free_info(t_info *info);
void	ft_error(t_game *game, char *str);

/*-------------------- init --------------------*/

/* init.c */
void	init(t_game *game);
void	init_map(t_map *map);
void	init_ray(t_ray *ray);
void	init_info(t_info *info);
void	init_player(t_player *player);

/*-------------------- keyboard --------------------*/

/* keyboard.c */
int		key_hook(t_game *game);
int		close_window(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);

/* move.c */
void	rotate(t_game *game);
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

/*-------------------- parsing --------------------*/

/* colors.c */
void	color_checker(t_game *game);
int		*set_color(t_game *game, char *line);
int		*color_convert(t_game *game, char **colors, int *c);
void	get_color(t_game *game, t_info *info, char *line, int j);

/* map_checker_2.c */
int		is_wspace(char c);
void	check_middle(t_game *game, int i, int j);
void	check_center(t_game *game, char **map, int i, int j);
void	check_border(t_game *game, char **map, int i, int j);

/* map_checker.c */
void	check_end(t_game *game);
void	map_checker(t_game *game);
void	check_char(t_game *game, char **map);
void	check_position(t_game *game, char **map);
void	check_player(t_game *game, char **map);

/* map.c */
void	map_extractor(t_game *game);
void	get_map(t_game *game, char **map, int i);
void	set_map(t_game *game, t_map *m, char **map, int w);

/* parsing_utils.c */
int		no_digit(char *str);
void	print_tab(char **tab);
void	print_int_star(int *tab);
int		get_width(t_map *map, int i);
int		get_height(t_game *game, char **map, int i);

/* parsing.c */
int		split_len(char **tab);
void	get_data(t_game *game);
void	parsing(t_game *game, int argc, char **argv);
int		get_info(t_game *game, char **map, int i, int j);
void	arg_checker(t_game *game, int argc, char **argv);

/* textures.c */
void	data_checker(t_game *game);
char	*get_path(char *line, int j);
void	texture_checker(t_game *game);
void	check_path(t_game *game, char *path);
void	get_textures(t_game *game, t_info *info, char *line, int j);

/* textures_2.c */
void	create_suite(t_game *game);
void	init_textures_game(t_game *game);
void	create_mlx_textures(t_game *game);
void	init_textures(t_game *game, t_ray *ray);
void	handle_textures(t_game *game, t_ray *ray, int x);

/*-------------------- player --------------------*/

/* player.c */
void	player_start_2(t_player *player);
void	player_start(t_player *player);

/*-------------------- src --------------------*/

/* main.c */
int		main(int argc, char **argv);

#endif