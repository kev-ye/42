/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:04:11 by kaye              #+#    #+#             */
/*   Updated: 2021/11/30 14:29:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS_H
# define CLASS_H

# include "defs.h"

enum e_path
{
	e_NO = 0,
	e_SO,
	e_WE,
	e_EA,
	e_F,
	e_C
};

/** @class t_io: members value use for io stream */
typedef struct s_io
{
	int		fd;
	int		ret;
	char	*line;
}	t_io;

/** @class t_map: members value use for save map and image path */
typedef struct s_map
{
	char			*path[PATHMAX];
	unsigned char	ceiling[COLORMAX];
	unsigned char	floor[COLORMAX];
	char			**map;
}	t_map;

/** 
 * @class t_img: members value use for create mlx image
 * @note tuto: https://harm-smits.github.io/42docs/libs/minilibx/images.html
 */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size;
	int		endian;
	int		width;
	int		height;
}	t_img;

/** @class t_player: members value use for player information */
typedef struct s_player
{
	char	direction;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	cam_height;
	double	speed;
	double	rot_speed;
}	t_player;

/** @class t_line: members value use for fill color / texture to image */
typedef struct s_line
{
	int		start;
	int		end;
	int		l_x;
	int		l_y;
	int		tex_x;
	int		tex_y;
}	t_line;

/** 
 * @class t_raycast: members value use for ray-casting technology
 * @note tuto: https://lodev.org/cgtutor/raycasting.html
 */
typedef struct s_raycast
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
}				t_raycast;

/** @class t_cub3d: main struct */
typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**config;
	t_map		map_info;
	t_img		mlx_img;
	t_img		tex_img[TEXMAX];
	t_player	player;
	BOOL		key[KEYMAX];
}	t_cub3d;

#endif
