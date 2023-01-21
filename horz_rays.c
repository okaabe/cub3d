/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horz_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:45:24 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/20 15:50:31 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	drawray(t_frame	*frameData, double ray_angle, double distance, int i)
{
	double	endx;
	double	endy;
	// double	deltax;
	// double	deltay;
	// int		pixels;

	endx = (frameData->player.x) + (cos(ray_angle) * distance);
	endy = frameData->player.y + (sin(ray_angle) * distance);
	frameData->rays[i].x = endx;
	frameData->rays[i].y = endy;
	// deltax = endx - frameData->player.x;
	// deltay = endy - frameData->player.y;
	// pixels = sqrt((deltax * deltax) + (deltay * deltay));
	// deltax /= pixels;
	// deltay /= pixels;
	// endx = frameData->player.x;
	// endy = frameData->player.y;
 }

void	find_hsteps(t_frame *frameData, t_vector_db *intercept,
		t_vector_db *step, int ray)
{
	intercept->y = (floor(frameData->player.y / TILE_SIZE)) * TILE_SIZE;
	if (frameData->rays[ray].isray_facing_down)
	{
		intercept->y += TILE_SIZE;
	}
	intercept->x = frameData->player.x + (intercept->y - frameData->player.y)
		/ tan(frameData->rays[ray].ray_angle);
	step->y = TILE_SIZE;
	if (frameData->rays[ray].isray_facing_up)
	{	
		step->y *= -1;
	}
	step->x = TILE_SIZE / tan(frameData->rays[ray].ray_angle);
	if (frameData->rays[ray].is_ray_facing_left && step->x > 0)
		step->x *= -1;
	if (frameData->rays[ray].isray_facing_right && step->x < 0)
		step->x *= -1;
}

double	check_y(t_frame *frameData, double y,	int ray)
{
	if (frameData->rays[ray].isray_facing_up)
		y--;
	return (y);
}

bool	verify(t_frame *framedata, t_vector_db horz_touch)
{
	if (horz_touch.x >= 0
		&& horz_touch.x <= (framedata->data.map_width * TILE_SIZE)
		&& horz_touch.y >= 0
		&& horz_touch.y <= (framedata->data.map_height * TILE_SIZE))
		return (true);
	return (false);
}

double	horz_rays(t_frame *frameData, int ray)
{
	t_vector_db	intercept;
	t_vector_db	step;
	t_vector_db	horz_touch;
	t_vector_db	player;

	player.x = frameData->player.x;
	player.y = frameData->player.y;
	find_hsteps(frameData, &intercept, &step, ray);
	horz_touch.x = intercept.x;
	horz_touch.y = intercept.y;
	while (verify(frameData, horz_touch))
	{
		if (is_wall(horz_touch.x, check_y(frameData, horz_touch.y, ray)
				, frameData))
		{
			return (calculate_distance(player, horz_touch));
		}
		else
		{
			horz_touch.x += step.x;
			horz_touch.y += step.y;
		}
	}
	return (0);
}
