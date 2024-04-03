/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:40:01 by kaye              #+#    #+#             */
/*   Updated: 2021/11/30 14:35:50 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "defs.h"
# include "class.h"

/* 
 * tools
*/
t_cub3d		*sglt(void);
uint32_t	create_rgb(int r, int g, int b);

/*
 * utils
*/
char		**lst2tab(t_list *to_tab);
size_t		strslen(char **sstr);
int			gnl(int const *fd, char **line,	void *to_free);
void		free_clean(void **to_free);

/*
 * exit / clean
*/
void		mlx_clean(void);
void		clean(void);
void		exit_clean(char *msg, char *file, int line);

/* 
 * parser
*/
void		config_parsing(char const *path);
BOOL		get_info_parsing(char *str,
				int const index, int const info, char const *cf_id);
int			info_config_parsing(void);
void		map_config_parsing(int constindex);
void		horizontal_check(char const *line, int consth_pos);
void		vertical_check(char **map, int const v_pos, int const h_pos);
void		map_parsing(void);

/*
 * engine
*/
/** @brief engine: game initialize */
void		player_initialize(void);
void		tex_initialize(void);

/** @brief engine: player move */
void		move_w(void);
void		move_s(void);
void		move_a(void);
void		move_d(void);

/** @brief engine: player rotation */
void		rot_left(void);
void		rot_right(void);

/** @brief engine: key control */
int			key_pressing(int keycode);
int			key_releasing(int keycode);
void		key_control(void);

/** @brief engine: start game */
void		start_game(void);

/** @brief engine: draw tools */
void		fill_color_vertically(t_line *l, unsigned int const color);
void		fill_text_vertically(t_line *l, t_img tex, t_raycast *ray);

/** @brief engine: fill color / texture to image */
void		drawing(t_raycast *ray);

/** @brief engine: ray-casting utils */
void		wall_hit(t_raycast *ray);
void		projection_dist_calculate(t_raycast *ray);
void		height_line_calculate(t_raycast *ray);
void		pixel_to_fill_stripe_calculate(t_raycast *ray);

/** @brief engine: do ray-casting */
void		do_raycasting(void);

#endif