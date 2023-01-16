/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 19:13:29 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/16 02:56:17 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	calculate_distance(t_vector_db first, t_vector_db sec)
{
	double	sum_x;
	double	sum_y;

	sum_x = pow(first.x - sec.x, 2);
	sum_y = pow(first.y - sec.y, 2);
	return (sqrt(sum_x + sum_y));
}

bool	if_facing_dowm(t_frame *frameData, int ray)
{
	if (frameData->rays[ray].ray_angle > 0
		&& frameData->rays[ray].ray_angle < M_PI)
	{
		return (true);
	}
	return (false);
}

bool	if_facing_right(t_frame *frameData, int ray)
{
	if (frameData->rays[ray].ray_angle < 0.5 * M_PI
		|| frameData->rays[ray].ray_angle > 1.5 * M_PI)
	{
		return (true);
	}
	return (false);
}

void	find_the_facing_of_ray(t_frame *frameData, int ray)
{
	frameData->rays[ray].isray_facing_down = if_facing_dowm(frameData, ray);
	frameData->rays[ray].isray_facing_up
		= !frameData->rays[ray].isray_facing_down;
	frameData->rays[ray].isray_facing_right = if_facing_right(frameData, ray);
	frameData->rays[ray].is_ray_facing_left
		= !frameData->rays[ray].isray_facing_right;
}

bool	is_wall(double tmp_x, double tmp_y, t_frame *frameData)
{
	int	x;
	int	y;

	x = tmp_x / TILE_SIZE;
	y = tmp_y / TILE_SIZE;
	if (frameData->data.map[y][x] == '0' && tmp_x != -1 && tmp_y != -1)
	{
		return (false);
	}
	else
		return (true);
}
