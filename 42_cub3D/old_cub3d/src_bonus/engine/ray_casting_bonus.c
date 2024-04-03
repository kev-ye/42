/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:05:42 by kaye              #+#    #+#             */
/*   Updated: 2021/03/01 19:46:17 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		touch_sprite(t_win *win)
{
	if (win->desc_info->map[(int)win->camera->pos_y]
			[(int)win->camera->pos_x] == '4')
	{
		effect_sound_h();
		win->desc_info->map[(int)win->camera->pos_y]
			[(int)win->camera->pos_x] = '0';
		if (win->player_life < 1.0)
			win->player_life += 0.33;
	}
	if (win->desc_info->map[(int)win->camera->pos_y]
			[(int)win->camera->pos_x] == '3')
	{
		effect_sound_m();
		win->desc_info->map[(int)win->camera->pos_y]
			[(int)win->camera->pos_x] = '0';
		if (win->player_life > 0.0)
			win->player_life -= 0.33;
	}
}

static void		ray_casting_regroup(
		t_win *win,
		t_ray_cast *ray)
{
	t_camera *cam;

	cam = win->camera;
	init_raycating_value_calc(cam, ray, win);
	step_calc_init_side_dist(cam, ray);
	wall_hit(ray, win);
	perpwalldist_and_heightline(cam, ray, win);
	mapping(ray, win);
	ray->zbuffer[ray->pix] = ray->perp_wall_dist;
	++ray->pix;
}

static void		effect(t_win *win)
{
	touch_sprite(win);
	life_bar(win);
	gun(win);
}

int				ray_casting(t_win *win)
{
	t_ray_cast *ray;

	if (!(ray = malloc(sizeof(t_ray_cast))))
		return (0);
	ft_bzero(ray, sizeof(t_ray_cast));
	if (!(ray->zbuffer = malloc(sizeof(double) * win->width)))
		return (0);
	ft_bzero(ray->zbuffer, sizeof(double) * win->width);
	while (ray->pix < win->width)
		ray_casting_regroup(win, ray);
	if (!(sprite_casting(win, ray)))
		return (0);
	effect(win);
	if (!win->save)
		mlx_put_image_to_window(win->mlx_ptr, win->win_ptr,
				win->img->img_ptr, 0, 0);
	free(ray->zbuffer);
	free(ray);
	if (win->player_life < 0.0)
		shut_down(win);
	return (1);
}
