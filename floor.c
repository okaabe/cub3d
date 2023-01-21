/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 02:54:42 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/20 17:54:25 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	f_c(t_frame	*frameData, int x_index, int y)
{
	int	color;
	int	end;
	int	start;

	if (y < MAP_HEIGHT / 2)
	{
		end = y;
		color = frameData->data.c;
		start = 0;
	}
	else
	{
		end = MAP_HEIGHT;
		color = frameData->data.f;
		start = y;
	}
	while (start < end)
	{
		my_mlx_pixel_put(&frameData->mlxdata, x_index, start, color);
		start++;
	}
}

t_texture	*get_texture(t_frame *frame_data, int i)
{
	if (frame_data->rays[i].ray_angle > 0
		&& frame_data->rays[i].ray_angle < M_PI && frame_data->rays[i].hor_hit)
		return (&frame_data->textures[S]);
	else if (frame_data->rays[i].ray_angle > M_PI / 2
		&& frame_data->rays[i].ray_angle < M_PI + (M_PI / 2)
		&& frame_data->rays[i].vert_hit)
		return (&frame_data->textures[W]);
	else if (frame_data->rays[i].ray_angle > M_PI
		&& frame_data->rays[i].ray_angle < 2 * M_PI
		&& frame_data->rays[i].hor_hit)
		return (&frame_data->textures[N]);
	return (&frame_data->textures[E]);
}
