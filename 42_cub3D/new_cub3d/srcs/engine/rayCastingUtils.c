/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayCastingUtils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:42:07 by kaye              #+#    #+#             */
/*   Updated: 2021/11/29 23:36:05 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_hit(t_raycast *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			if (ray->step_x == 1)
				ray->side = e_NO;
			else if (ray->step_x == -1)
				ray->side = e_SO;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			if (ray->step_y == 1)
				ray->side = e_WE;
			else if (ray->step_y == -1)
				ray->side = e_EA;
		}
		if (sglt()->map_info.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	projection_dist_calculate(t_raycast *ray)
{
	t_player const	ply = sglt()->player;

	if (ray->side == 0 || ray->side == 1)
		ray->perp_wall_dist = (ray->map_x - ply.pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ply.pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	height_line_calculate(t_raycast *ray)
{
	ray->line_height = (int)(W_HEIGHT / ray->perp_wall_dist);
}

void	pixel_to_fill_stripe_calculate(t_raycast *ray)
{
	t_player const	ply = sglt()->player;

	ray->draw_start = (-ray->line_height / 2
			+ ((W_HEIGHT / 2) * ply.cam_height));
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2
			+ ((W_HEIGHT / 2) * ply.cam_height));
	if (ray->draw_end >= W_HEIGHT)
		ray->draw_end = W_HEIGHT;
}
