/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:28:22 by asangerm          #+#    #+#             */
/*   Updated: 2024/07/11 22:34:58 by nfradet          ###   ########.fr       */
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
# define GAME_WIDTH 640
# define GAME_HEIGHT 480
# define MINIMAP_SIZE 7
# define TILE_SIZE 20
# define BORDER_SIZE 2

# define MOVE_SPEED 0.02
# define COEFF_MOUSE_ROTA 10000.0

# define K_UP 119
# define K_DOWN 115
# define K_LEFT 97
# define K_RIGHT 100
# define K_SPACE 32
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
# define INVALID_DOOR "Door not correctly placed"

typedef struct s_info
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*cd_path;
	char		*od_path;
	char		*fl_path;
	char		*ce_path;
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
	int			open_door;//indique si il essaie d'ouvrir une porte
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
	double	dir_y0;//rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
	double	dir_x0;
	double	dir_y1;
	double	dir_x1;
	int		p;//Current y position compared to the center of the screen
	double	posz;//Vertical position of the camera.
	double	row_dist;//Horizontal distance from the camera to the floor.
	double	f_step_x;//the real world step vector we have to add for each x.
	double	f_step_y;//adding step by step avoids multiplications with a weight
	double	f_x;//real world coordinates of the leftmost column.
	double	f_y;
	int		cellx;//the cell coord is from the integer of floorX and floorY
	int		celly;
	int		t_x;//get the texture coordinate from the fractional part
	int		t_y;
	t_image	cimage;
	t_image	fimage;
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
	t_image	cd;
	t_image	od;
	t_image	floor;
	t_image	ceiling;
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
	t_list		*lst_ray;
	int			last_x;
	int			is_rota_stopping;
	double		ms_rota;
	double		previous_time;
	double		current_time;
	int			frame_count;
	int			fps;
}		t_game;

/*-------------------- display --------------------*/

void	open_door(t_game *game);

/* draw_utils.c */
int		get_sign(double nb);
void	free_star(int **tab, int h);
void	set_pixel(t_image *image, int y, int x, int color);

/* drawing.c */
int		draw(t_game *game);
int		color_change(int *color);
void	print_img_ray(int **text, t_game *game);
void	draw_line(t_game *game, int x);
void	free_texture(t_game *game, t_textures *text);

/* floor_ceil.c */
void	floor_ceiling(t_game *game);
void	init_floor_ceiling_texture(t_game *game, t_ray *ray);
void	print_floor_ceiling(t_game *game, t_ray *ray, int y);
void	init_floor_ceiling(int y, t_ray *ray, t_player *player);

/* fps.c */
double	get_time_in_seconds(void);
void	calculate_and_display_fps(t_game *game);

/* minimap.c */
void	handle_outline(t_game *game);
void	draw_map(t_game *game, int i, int j);
void	handle_drawing(t_game *game, int i, int j);
void	draw_square(t_game *game, int x, int y, int color);
void	print_image(int **mini_map, t_game *game, int tile_size);

/* player_icon.c */
void	draw_player(t_game *game, int x, int y, int colorp);
void	draw_triangle_east(t_game *game, int x, int y, int colorp);
void	draw_triangle_west(t_game *game, int x, int y, int colorp);
void	draw_triangle_north(t_game *game, int x, int y, int colorp);
void	draw_triangle_south(t_game *game, int x, int y, int colorp);

/* raycasting.c */
void	raycasting(t_game *game);
void	dda(t_game *game, t_ray *ray);
void	init_dda(t_ray *ray, t_player *player);
t_ray	*init_raycasting(int x, t_player *player);


/* raycasting_utils.c */
void	add_door_ray(t_game *game, t_ray *ray);
void	wall_height(t_game *game, t_ray *ray, t_player *player);

/*-------------------- ending --------------------*/

/* ending.c */
void	end(t_game *game);
void	free_tab(char **tab);
void	free_map(t_map *map);
void	free_info(t_info *info);
void	ft_error(t_game *game, char *str);

/*-------------------- init --------------------*/

/* init_2.c */
void	init_textures_game(t_image *img);
void	init_text(t_game *game, int tile_size);
void	init_textures(t_game *game, t_ray *ray);

/* init.c */
void	init(t_game *game);
void	init_map(t_map *map);
void	init_info(t_info *info);
void	init_player(t_player *player);

/*-------------------- keyboard --------------------*/

/* keyboard.c */
int		key_hook(t_game *game);
int		close_window(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		mouse_move(int x, int y, t_game *game);

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
void	check_player(t_game *game, char **map);
void	check_position(t_game *game, char **map);

/* map.c */
void	check_doors(t_game * game);
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
void	create_suite_suite(t_game *game);
void	create_mlx_textures(t_game *game);
void	handle_textures(t_game *game, t_ray *ray, int x);

/*-------------------- player --------------------*/

/* player.c */
void	player_start(t_player *player);
void	player_start_2(t_player *player);

/*-------------------- src --------------------*/

/* main.c */
int		main(int argc, char **argv);

#endif