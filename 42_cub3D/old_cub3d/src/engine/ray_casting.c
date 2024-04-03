/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:05:42 by kaye              #+#    #+#             */
/*   Updated: 2021/03/01 19:46:25 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{
		ray_casting_regroup(win, ray);
		++ray->pix;
	}
	if (!(sprite_casting(win, ray)))
		return (0);
	if (!win->save)
		mlx_put_image_to_window(win->mlx_ptr, win->win_ptr,
				win->img->img_ptr, 0, 0);
	free(ray->zbuffer);
	free(ray);
	return (1);
}
