/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horz_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:45:24 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/11 21:22:35 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	find_the_facing_of_ray(t_frame *frameData, int ray)
{
	printf("angle %f \n", frameData->rays[ray].ray_angle);
	frameData->rays[ray].isray_facing_down = frameData->rays[ray].ray_angle > 0 && frameData->rays[ray].ray_angle < M_PI;
	frameData->rays[ray].isray_facing_up = !frameData->rays[ray].isray_facing_down;
	frameData->rays[ray].isray_facing_right = frameData->rays[ray].ray_angle < 0.5 * M_PI || frameData->rays[ray].ray_angle > 1.5 * M_PI;
	frameData->rays[ray].is_ray_facing_left = !frameData->rays[ray].isray_facing_right; 
}

bool is_wall(double tmp_x, double tmp_y, t_frame* frameData)
{
    int x = tmp_x / 32;
    int y = tmp_y / 32;
    if (frameData->data.map[y][x] == '0' && tmp_x != -1 && tmp_y != -1)
    {
        return (false);
    }
	else
		return (true);
}


double calculate_distance(t_vector_db first, t_vector_db sec)
{
	double sum_x;
	double sum_y;

	sum_x = pow(first.x - sec.x, 2);
	sum_y = pow(first.y - sec.y, 2);
	return (sqrt(sum_x + sum_y));
}

void drawray(t_frame* frameData, double ray_angle, double distance)
{
	t_vector_db player;

	double endX = (frameData->player.x) + (cos(ray_angle) * distance);
	double endY = frameData->player.y + (sin(ray_angle) * distance);
	double deltaX = endX - frameData->player.x;
	double deltaY = endY - frameData->player.y;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	endX = frameData->player.x;
	endY = frameData->player.y;
	while (pixels)
	{
	    my_mlx_pixel_put(&frameData->mlxData, endX, endY, 0xcd6155);
	    endX += deltaX;
	    endY += deltaY;
	    --pixels;
	}
}

void	find_hsteps(t_frame *frameData, t_vector_db *intercept, t_vector_db *step, int ray)
{
	intercept->y = (floor(frameData->player.y / 32)) * 32;
	
	if (frameData->rays[ray].isray_facing_down)
	{
		// printf("player facing down\n");	
		intercept->y += 32;
	}
	intercept->x = frameData->player.x + (intercept->y - frameData->player.y) / tan(frameData->rays[ray].ray_angle); 
	
	step->y = 32;
	if (frameData->rays[ray].isray_facing_up)
	{	
		step->y *= -1;
	}
	step->x = 32 / tan(frameData->rays[ray].ray_angle);
	if (frameData->rays[ray].is_ray_facing_left && step->x > 0)
		step->x *= -1;
	if (frameData->rays[ray].isray_facing_right && step->x < 0)
		step->x *= -1;
		
}

double check_y(t_frame *frameData,double y,	int ray)
{
	if (frameData->rays[ray].isray_facing_up)
		y--;
	return (y);
}

double	Horz_rays(t_frame *frameData, int ray)
{
	t_vector_db intercept;
	t_vector_db	step;
	t_vector_db	horz_touch;
	t_vector_db	player;
	
	player.x = frameData->player.x;
	player.y = frameData->player.y;
	find_hsteps(frameData,&intercept, &step, ray);
	horz_touch.x = intercept.x;
	horz_touch.y = intercept.y;

	while (horz_touch.x >= 0 && horz_touch.x <= (frameData->data.map_width * 32) && horz_touch.y >= 0 && horz_touch.y <= (frameData->data.map_height * 32))
	{
		if(is_wall(horz_touch.x, check_y(frameData, horz_touch.y, ray), frameData))
		{
			printf("horz_touh->x %f horz_touh->y %f\n", floor(horz_touch.x / 32), floor(horz_touch.y / 32));
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