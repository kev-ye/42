/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:11:06 by kaye              #+#    #+#             */
/*   Updated: 2021/03/02 12:30:20 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include "libft.h"
# include <time.h>

/*
** KEY CODE MACOS / LINUX
*/
# if defined (__APPLE__) && (__MACH__)
#  define KEY_CODE_ESC 53
#  define KEY_CODE_W 13
#  define KEY_CODE_S 1
#  define KEY_CODE_A 0
#  define KEY_CODE_D 2
#  define KEY_CODE_LEFT 123
#  define KEY_CODE_RIGHT 124
#  define KEY_CODE_UP 126
#  define KEY_CODE_DOWN 125
#  define RED_CROSS 17
#  define SOUND "afplay"
#  define KILL_SOUND "killall afplay"
# else
#  define KEY_CODE_ESC 65307
#  define KEY_CODE_W 119
#  define KEY_CODE_S 115
#  define KEY_CODE_A 97
#  define KEY_CODE_D 100
#  define KEY_CODE_LEFT 65361
#  define KEY_CODE_RIGHT 65363
#  define KEY_CODE_UP 65362
#  define KEY_CODE_DOWN 65364
#  define RED_CROSS 33
#  define SOUND "aplay"
#  define KILL_SOUND "killall aplay"
# endif

/*
** SHELL PRINT CODE
*/
# define S_NONE "\033[0m"
# define S_BLACK "\033[0;30m"
# define S_RED "\033[0;31m"
# define S_GREEN "\033[0;32m"
# define S_YELLOW "\033[0;33m"
# define S_BLUE "\033[0;34m"
# define S_PURPLE "\033[0;35m"
# define S_CYAN "\033[0;36m"
# define S_CLRLINE "\033[K\r"

/*
** COLOR CODE
*/
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define WHITE 0x00FFFFFF

/*
** MSG HUD
*/
# define MSG1 "PRESS ESC     : QUIT GAME"
# define MSG2 "PRESS W S A D : MOVE"
# define MSG3 "PRESS ^ v < > : CAMERA"

/*
** STRUCT - CAMERA / PLAYER
**
** Pos_*    : The start position
** Dir_*    : The initial direction vector
** Plane_*  : The 2d raycaster version of camera plane
*/
typedef struct	s_camera
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	cam_height;
	double	speed;
	double	rot_speed;
}				t_camera;

/*
** STURCT - RAY CASTING
**
** - Camera_x       : The camera plane current x coordinate of
**                    the screen represents.
** - Ray_dir_*      : Direction vector.
** - Map_*          : The current square of the map the ray is in.
** - Side_dist_*    : The distance the ray has to travel from its start
**                    position to the first x and y side.
** - Delta_dist_*   : The distance the ray has to travel to go from 1 x side
**                    or y side to the next x or y side.
** - Perp_wall_dist : The length of the ray.
** - Step_*         : Direction to step in x or y direction. (either +1 or -1)
** - Hit            : Wall hit.
** - Side           : North and south or west and east wall hit.
** - Line_height    : The height of line to draw on screen.
*/
typedef struct	s_ray_cast
{
	int			pix;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		*zbuffer;
}				t_ray_cast;

/*
** STRUCT - IMAGE
**
** Bpp      : The number of bits per pixels.
** Line_len : The size of a line.
** Endian   : Endian.
*/
typedef struct	s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}				t_img;

/*
** STRUCT - EVENT KEY
*/
typedef struct	s_key
{
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
	int		key_left;
	int		key_right;
	int		key_up;
	int		key_down;
	int		key_h;
	int		key_m;
}				t_key;

/*
** STRUCT - DRAW LINE
**
** Line_*   : Draw x/y coordinate.
** Draw_*   : Start/end draw point.
** tex_*    : About textured.
*/
typedef struct	s_line
{
	int		line_x;
	int		line_y;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		tex_y;
}				t_line;

/*
** STRUCT - DESCRITION UTILS
*/
typedef struct	s_desc
{
	int		map;
	int		player;
	int		r;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		s;
	int		f;
	int		c;
	int		m;
	int		b;
	int		l;
	int		g;
}				t_desc;

/*
** STRUCT - DESCRIPTION INFORMATION
**
** R_*          : The resolution of window.
** Path_*       : THe different picture path.
** Color_*      : Floor and ceiling color code on RGB.
** Player_*     : The start position.
** player_dir   : The start direction.
** Map          : Map
*/
typedef struct	s_desc_info
{
	t_desc	desc;
	char	**map;
	int		map_y;
	int		map_x;
	int		r_x;
	int		r_y;
	int		color_f;
	int		color_c;
	int		player_x;
	int		player_y;
	int		player_dir;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char	*path_s;
	char	*path_m;
	char	*path_b;
	char	*path_l;
	char	*path_g;
}				t_desc_info;

/*
** STRUTC - SPRITES COORDINATE
*/
typedef struct	s_sprite
{
	int		x;
	int		y;
}				t_sprite;

/*
** STRUTC - SPRITES CASTING
*/
typedef struct	s_sp_cast
{
	t_sprite		*sprite;
	int				sp_amount;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				tex_x;
	int				tex_y;
	int				y;
	unsigned int	color;
}				t_sp_cast;

/*
** STRUCT - FOR FUCKING NORME
*/
typedef struct	s_var
{
	int r;
	int	i;
	int j;
	int len;
}				t_var;

/*
** STRUCT - GLOBAL
*/
typedef struct	s_win
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
	int			save;
	t_desc_info	*desc_info;
	t_camera	*camera;
	t_key		*key_code;
	t_img		*img;
	t_img		**texture;
	t_img		**sprite;
	t_img		*life;
	t_img		*gun;
	t_img		*mini_map;
	int			pix_size;
	double		player_life;
	clock_t		sound_begin_time;
}				t_win;

/*
** ENGINE - DRAW / IMAGE
*/
t_img			*new_image(t_win *win, int size_x, int size_y);
void			pixel_put_color(t_img *img, int x, int y, unsigned int color);
void			draw_vertical_color(t_line *line, t_win *win,
														unsigned int color);
void			draw_vertical_tex(t_line *line, t_win *win, t_img *texture,
															t_ray_cast *ray);

/*
** ENGINE - TEXTURE
*/
int				set_texture(t_win *win, const char *path, int index);
int				load_texture(t_win *win);
int				init_tex(t_win *win);

/*
** ENGINE - SPRITE CASTING
**
** Step of sptite casting :
**
** Sort sprites from far to close (sort_sprite).
** After sorting the sprites, do the projection and draw them (sprite_casting).
** Translate sprite position to relative to camera (sprite_projection).
** Transform sprite with the inverse camera matrix (sprite_projection):
**
** [ planeX   dirX ] -1                                    [ dirY      -dirX ]
** [               ]     =  1/(planeX*dirY-dirX*planeY) *  [                 ]
** [ planeY   dirY ]                                       [ -planeY  planeX ]
**
** Required for correct matrix multiplication (sprite_projection).
** Calculate height of the sprite on screen (sprite_draw).
** Calculate lowest and highest pixel to fill in current stripe (sprite_draw).
** Calculate width of the sprite (sprite_draw).
** Loop through every vertical stripe of the sprite on screen (sprite_drawing).
** With the conditions in the if are (sprite_drawing):
** 1) it's in front of camera plane so you don't see things behind you.
** 2) it's on the screen (left).
** 3) it's on the screen (right).
** 4) ZBuffer, with perpendicular distance.
** Loop for every pixel of the current stripe (sprite_drawing).
** (sprite_drawing + pixel_put_sprite).
** Get current color from the texture (sprite_drawing + pixel_put_sprite).
** Paint pixel if it isn't the invisible color(sprite_drawing + paint_pixel).
*/
int				set_sprites(t_win *win, const char *path, int index);
int				load_sprites(t_win *win);
int				init_sprite(t_win *win);
int				get_sprite_amount(t_win *win);
t_sp_cast		*sprite_cast_init(t_win *win);
t_sp_cast		*get_sprite_pos(t_win *win);
void			sort_sprite(t_win *win, t_sp_cast *sp_cast);
void			sprite_projection(t_win *win, t_sp_cast *sp_cast, int i);
void			sprite_draw(t_win *win, t_sp_cast *sp_cast, t_ray_cast *ray,
																		int i);
void			sprite_drawing(t_win *win, t_sp_cast *sp_cast, t_ray_cast *ray,
																		int i);
void			pixel_put_sprite(t_win *win, t_sp_cast *sp_cast, int i);
void			paint_pixel(t_win *win, t_sp_cast *sp_cast, int i);
int				sprite_casting(t_win *win, t_ray_cast *ray);

/*
** ENGINE - RAY CASTING
**
** Step of ray casting (check with the "STRUCT - RAY CASTING"):
**
** Calculate ray postion and direction (init_raycating_value_calc).
** Get which box of the map we're in (init_raycating_value_calc).
** Get lenght of ray from one x or y-side to next x or y-side
** (init_raycating_value_calc).
** Calculate step and initial side distance (step_calc_init_side_dist).
** Perform DDA (wall_hit).
** Jump to next map square, or in x-direction, or in y-direction (wall_hit).
** Check if ray hs hit a wall (wall_hit).
** Calculate distance projected on camera direction
** (perpwalldist_and_heightline).
** Calculate height of line to draw on screen (perpwalldist_and_heightline).
** Calculate lowest and highest pixel to fill in current stripe
** (perpwalldist_and_heightline).
** Textured / colored + draw -> check "ENGINE - MAPPING".
** Move -> check "ENGINE - PLAYER MOUVEMENT".
** rotation -> check "ENGINE - CAMERA TURN".
*/
void			init_raycating_value_calc(t_camera *cam, t_ray_cast *ray,
																t_win *win);
void			step_calc_init_side_dist(t_camera *cam, t_ray_cast *ray);
void			wall_hit(t_ray_cast *ray, t_win *win);
void			perpwalldist_and_heightline(t_camera *cam, t_ray_cast *ray,
																t_win *win);
int				ray_casting(t_win *win);

/*
** ENGINE - LIFE BAR
*/
int				set_life_img(t_win *win, const char *path);
void			life_bar(t_win *win);

/*
** ENGINE - GUN
*/
int				set_gun_img(t_win *win, const char *path);
void			gun(t_win *win);

/*
** ENGINE - SOUND
*/
void			game_sound();
void			effect_sound_h();
void			effect_sound_m();
void			play_game_sound(t_win *win);
void			game_sound_loop(t_win *win);

/*
** ENGINE - MINI MAP
*/
int				init_mini_map(t_win *win);
void			mini_map(t_win *win);

/*
** ENGINE - INIT CAMERA / PLAYER
*/
int				init_camera(t_win *win);

/*
** ENGINE - PLAYER MOUVEMENT
*/
void			move_w(t_win *win);
void			move_s(t_win *win);
void			move_a(t_win *win);
void			move_d(t_win *win);

/*
** ENGINE - CAMERA ROTATION
*/
void			turn_left(t_win *win);
void			turn_right(t_win *win);
void			turn_up(t_win *win);
void			turn_down(t_win *win);

/*
** ENGINE - MAPPING
*/
void			draw_side(t_ray_cast *ray, t_win *win, t_line *line,
																double wall_x);
void			draw_ceiling_floor(t_win *win, t_line *line, t_ray_cast *ray);
void			mapping(t_ray_cast *ray, t_win *win);

/*
** EVENTS - KEYS
*/
int				event_key_press(int keycode, t_win *win);
int				event_key_release(int keycode, t_win *win);
int				event_key(t_win *win);
int				init_key(t_win *win);

/*
** EVENTS - EVENTS
*/
int				event_destroy_win(t_win *win);
int				event_loop(t_win *win);

/*
** PARSER - INIT DESCRIPTION
*/
t_desc			init_desc();
t_desc_info		*init_desc_info();

/*
** PARSER - GET INFORMATION
*/
int				get_resoltion(char *line, t_desc_info *desc_info);
int				check_and_get_color(char *s);
int				get_floor_color(char *line, t_desc_info *desc_info);
int				get_ceiling_color(char *line, t_desc_info *desc_info);
int				get_path(char *line, t_desc_info *desc_info);

/*
** PARSER - CHECK FILE
*/
int				check_file_name(const char *path);
int				check_file_line(char *line, t_desc *desc,
													t_desc_info *desc_info);
int				check_file_line_info_done(t_desc desc);
int				check_map_ready(t_desc desc);
int				check_no_map(char *line, t_desc *desc);
int				check_map_norm(char *line);
int				check_path(t_desc_info *desc_info);
t_desc_info		*check_file(t_win *win, const char *path);

/*
** PARSER - MAP
*/
char			**get_map(const char *path, int *len_max_y, int *len_max_x);
char			**get_map2(const char *path, int fd, int y_max, int x_max);
int				map_line(char *line);
char			**get_player_place(char **map, int *p_x, int *p_y,
												t_desc_info *desc_info);
int				check_map_x(char **map, int y, int x);
int				check_map_y(char **map, int y, int x, int len_y_max);
int				check_map(char **map, int len_y_max);

/*
** INIT / UTILS
*/
void			msg_error(t_win *win, char *msg);
int				create_rgb(int r, int g, int b);
void			free_split(char **s);
void			free_desc_info(t_desc_info *desc_info);
void			free_img_sprite(t_win *win);
void			free_img_effect(t_win *win);
void			free_win(t_win *win);
void			free_img_tex(t_win *win);
void			shut_down(t_win *win);
void			make_bmp(t_win *win);
void			put_hud(t_win *win);

#endif
