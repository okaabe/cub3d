/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:39:44 by aamoussa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/12 00:29:49 by aamoussa         ###   ########.fr       */
=======
/*   Updated: 2023/01/12 16:50:06 by ahamdy           ###   ########.fr       */
>>>>>>> 8c3a834e1a3ae16234e04392fc4f1860d35f4273
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	find_vsteps(t_frame *frameData, t_vector_db *intercept, t_vector_db *step, int ray)
{
	intercept->x = (floor(frameData->player.x / TILE_SIZE)) * TILE_SIZE;
	
	if (frameData->rays[ray].isray_facing_right)
		intercept->x += TILE_SIZE;
	intercept->y = frameData->player.y + (intercept->x - frameData->player.x) * tan(frameData->rays[ray].ray_angle);

	step->x = TILE_SIZE;
	if (frameData->rays[ray].is_ray_facing_left)
	{	
		step->x *= -1;
	}
	step->y = TILE_SIZE * tan(frameData->rays[ray].ray_angle);
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

	while (vert_touch.x >= 0 && vert_touch.x <= (frameData->data.map_width * TILE_SIZE) && vert_touch.y >= 0 && vert_touch.y <= (frameData->data.map_height * TILE_SIZE))
	{
		if(is_wall(check_x(frameData, vert_touch.x, ray), vert_touch.y, frameData))
		{	
			frameData->rays[ray].vert_touch = vert_touch;
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