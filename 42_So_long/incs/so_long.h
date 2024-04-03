/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 17:51:12 by kaye              #+#    #+#             */
/*   Updated: 2021/07/05 20:15:24 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <mlx.h>
# include "libft.h"
# if defined __linux__
#  include <stdint.h>
# endif

/* KEY CODE MACOS / LINUX */
# if defined (__APPLE__) && (__MACH__)
#  define KEY_CODE_ESC 53
#  define KEY_CODE_W 13
#  define KEY_CODE_S 1
#  define KEY_CODE_A 0
#  define KEY_CODE_D 2
#  define RED_CROSS 17
# else
#  define KEY_CODE_ESC 65307
#  define KEY_CODE_W 119
#  define KEY_CODE_S 115
#  define KEY_CODE_A 97
#  define KEY_CODE_D 100
#  define RED_CROSS 33
# endif

/* EXIT CODE */
# define SUCCESS 0
# define FAILURE 1
# define NOTHING -1

/* ERROR MSG */
# define E_MALLOC "Malloc/mlx error"

/* MLX */
# define WIDTH 1000
# define HEIGTH 1000

/* TEX */
# define TEX_NBR 5

/* STRUCT - IMAGE */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* STRUCT - PARSER */
typedef struct s_parser
{
	int		fd;
	int		ret;
	char	*line;
	int		len;
	int		tmp_len;
	int		i;
}	t_parser;

/* STRUCT - PLAYER */
typedef struct s_player
{
	int	x;
	int	y;
	int	count;
}	t_player;

/* STRUCT - GLOBAL */
typedef struct s_win
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			key_code[4];
	char		**map;
	int			collectible;
	int			len_frame_x;
	int			len_frame_y;
	t_player	player;
	t_img		*img;
	t_img		tex[TEX_NBR];
}	t_win;

/* ENGINE */
void		so_long(void);
void		pixel_put_color(int x, int y, uint32_t color);
void		move_w(void);
void		move_s(void);
void		move_a(void);
void		move_d(void);

/* EVENTS */
int			event_loop(void);
int			event_destroy_win(void);
int			event_key_press(int keycode);
int			event_key_release(int keycode);
int			event_key(void);
int			init_key(void);

/* PARSER */
void		parsing(char *path);
t_parser	parsing_check(char *path);
void		load_tex(void);

/* UTILS */
void		__free__(void *ptr);
int			__exit__(char *msg, void *ptr, int fd, int ret);
int			__open__(char *path, const int flag);
t_win		*singleton(void);

#endif