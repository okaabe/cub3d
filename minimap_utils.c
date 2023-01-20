/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 01:30:53 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/20 11:37:59 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	check(t_frame *framedata, int x, int y)
{
	if ((x >= 0 && x < framedata->data.map_width)
		&& (y >= 0 && y < framedata->data.map_height))
	{	
		return (true);
	}
	return (false);
}

void	playerdirection(t_frame	*framedata, double x, double y)
{
	double	endx;
	double	endy;
	double	deltax;
	double	deltay;
	int		pixels;

	endx = x + (cos(framedata->player.rotation_angle) * 15);
	endy = y + (sin(framedata->player.rotation_angle) * 15);
	deltax = endx - x;
	deltay = endy - y;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	endx = x;
	endy = y;
	while (pixels)
	{
		my_mlx_pixel_put(&framedata->mlxdata, endx, endy, 0xcd6155);
		endx += deltax;
		endy += deltay;
		--pixels;
	}
}

void	update_player_position(t_frame *framedata, double p_x, double p_y)
{
	t_vector	index;
	int			r;
	int			theta;
	int			x;
	int			y;

	theta = 0;
	r = 5;
	index.y = p_y;
	index.x = p_x;
	while (r)
	{
		theta = 0;
		while (theta <= 360)
		{
			x = index.x + r * cos((theta * M_PI) / 180.0);
			y = index.y + r * sin((theta * M_PI) / 180.0);
			my_mlx_pixel_put(&framedata->mlxdata,
				x * MINI_MAP_SIZE, y * MINI_MAP_SIZE,
				0xcd6155);
			theta++;
		}
	r--;
	}
}
