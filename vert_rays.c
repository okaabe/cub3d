/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:39:44 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/11 04:13:11 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	find_vsteps(t_frame *frameData, t_vector_db *intercept, t_vector_db *step, int ray)
{
	intercept->x = (floor(frameData->player.x / 32)) * 32;
	
	if (frameData->rays[ray].isray_facing_right)
		intercept->x += 32;
	intercept->y = frameData->player.y + (intercept->x - frameData->player.x) * tan(frameData->rays[ray].ray_angle);

	step->x = 32;
	if (frameData->rays[ray].is_ray_facing_left)
	{	
		step->x *= -1;
	}
	step->y = 32 * tan(frameData->rays[ray].ray_angle);
	if (frameData->rays[ray].isray_facing_up && step->y > 0)
		step->y *= -1;
	if (frameData->rays[ray].isray_facing_down && step->y < 0)
		step->y *= -1;
	
}

double check_x(t_frame *frameData, double x, int ray)
{
	if (frameData->rays[ray].is_ray_facing_left)
		x--;
	return (x);
}

double	vert_rays(t_frame *frameData, int ray)
{
	t_vector_db intercept;
	t_vector_db	step;
	t_vector_db	vert_touch;
	t_vector_db	player;
	
	player.x = frameData->player.x;
	player.y = frameData->player.y;
	find_vsteps(frameData,&intercept, &step, ray);
	vert_touch.x = intercept.x;
	vert_touch.y = intercept.y;

	while (vert_touch.x >= 0 && vert_touch.x <= (frameData->data.map_width * 32) && vert_touch.y >= 0 && vert_touch.y <= (frameData->data.map_height * 32))
	{
		if(is_wall(check_x(frameData, vert_touch.x, ray), vert_touch.y, frameData))
		{
			return (calculate_distance(player, vert_touch));	
		}
		else
		{
			vert_touch.x += step.x;
			vert_touch.y += step.y;
		}
	}
	return (0);		
}